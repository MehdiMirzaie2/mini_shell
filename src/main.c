/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:03:38 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/17 13:14:35 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"
#include "libft.h"
#include "lexer.h"
#include "ast.h"

static void	handle_command(t_mshctx *msh, int *exit_status)
{
	if (env_get(msh->env, "MSHDBG"))
		tlst_print(msh->lst);
	msh->ast = ast_build(msh->lst);
	if (msh->ast)
	{
		ast_expandall(msh->ast, msh->env);
		process_ast(*msh, &msh->env, exit_status);
		ast_memman(&msh->ast, E_ASTLINK, true);
	}
	env_set(msh->env, msh->exitvar, ft_itoa(WEXITSTATUS(*exit_status)));
}

void	init_rl(t_env *our_env, int	*exit_status)
{
	t_mshctx	msh;

	msh = (t_mshctx){0};
	msh.exitvar = ft_strdup("?");
	msh.env = our_env;
	while (1)
	{
		init_termios();
		signal(SIGINT, handle_sigint);
		rl_gets(&msh);
		if (msh.line == NULL || *msh.line == '\0')
			continue ;
		reset_termios();
		msh.lst = tlst_create(msh.line);
		msh.exit_code = tlst_syntax_check(msh.lst);
		if (!msh.exit_code)
			handle_command(&msh, exit_status);
		else
			env_set(msh.env, msh.exitvar, ft_itoa(msh.exit_code));
		tlst_destroy(msh.lst);
		msh.lst = NULL;
	}
}

void	increment_shell_levell(t_env *env)
{
	char	*prev;
	int		next;

	prev = env_get(env, "SHLVL");
	next = 1;
	if (prev && ((*prev == '-' && ft_isdigit(prev[1])) || ft_isdigit(*prev)))
		next = ft_atoi(prev) + 1;
	else if (prev && !*prev)
		next = 0;
	if (next < 0)
		next = 0;
	if (next >= 1000)
	{
		ft_printf_fd(2, "msh: warning: shell level (%S)"
			" too high, resetting to 1\n", ft_itoa(next));
		next = 1;
	}
	env_set(env, "SHLVL", ft_itoa(next));
}

int	main(int argc, char **argv, char **env)
{
	t_env		*our_env;
	static int	exit_status = 1;

	(void)argv;
	(void)argc;
	our_env = malloc(sizeof(t_env));
	create_env(our_env, env);
	increment_shell_levell(our_env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_rl(our_env, &exit_status);
	free_env(our_env, true);
	return (0);
}
