/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:03:38 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/17 11:58:18 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"
#include "libft.h"
#include "lexer.h"
#include "ast.h"
void    init_termioswords(void)
{
    struct termios    t;

    tcgetattr(0, &t);
    t.c_lflag = t.c_lflag & ~ECHO;
    tcsetattr(0, TCSANOW, &t);
}

void    reset_termioswords(void)
{
    struct termios    t;

    tcgetattr(0, &t);
    t.c_lflag = t.c_lflag | ECHO;
    tcsetattr(0, TCSANOW, &t);
}
char	*rl_gets(t_mshctx *msh)
{
	char		buff[PATH_MAX + 1];
	static char	*prev_path;
	char		*path;

	if (msh->prompt)
		free(msh->prompt);
	path = buff;
	if (!getcwd(buff, PATH_MAX + 1))
		path = prev_path;
	prev_path = path;
	msh->prompt = ft_strfmt("%s> ", path);
	if (msh->line)
		free(msh->line);
	if (!isatty(0))
	{	
		init_termioswords();
		msh->line = readline(NULL);
		//reset_termios();
		reset_termioswords();
	}
	else
		msh->line = readline(msh->prompt);
	if (msh->line == NULL)
	{
		int e_value = EXIT_SUCCESS;
		if (env_get(msh->env, "?") != NULL)
			e_value = ft_atoi(env_get(msh->env, "?"));
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		free_mshctx(*msh);
		delete_tempfile();
		exit(e_value);
	}
	if (msh->line && *msh->line)
		add_history(msh->line);
	return (msh->line);
}

void	init_rl(t_env *our_env, int	*exit_status)
{
	char *const	question = ft_strdup("?");
	t_mshctx	msh;

	msh = (t_mshctx){0};
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
		{
			if (env_get(msh.env, "MSHDBG"))
				tlst_print(msh.lst);
			msh.ast = ast_build(msh.lst);
			if (msh.ast)
			{
				ast_expandall(msh.ast, msh.env);
				process_ast(msh, &msh.env, exit_status);
				ast_memman(&msh.ast, E_ASTLINK, true);
			}
			env_set(msh.env, question, ft_itoa(WEXITSTATUS(*exit_status)));
		}
		else
			env_set(msh.env, "?", ft_itoa(msh.exit_code));
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
