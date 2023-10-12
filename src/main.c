/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:03:38 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/12 15:46:25 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"
#include "libft.h"
#include "lexer.h"
#include "ast.h"

char	*rl_gets(char **line_read, char *header)
{
	/*if (*line_read)*/
	/*{*/
	/*    free(*line_read);*/
	/*    *line_read = NULL;*/
	/*}*/
	*line_read = readline(header);
	if (!(*line_read))
	{
		delete_tempfile();
		exit(EXIT_SUCCESS);
	}
	if (*line_read && **line_read)
		add_history(*line_read);
	return (*line_read);
}

void	init_rl(t_env *our_env, int	*exit_status)
{
	static char	*line_read = NULL;
	char		buff[PATH_MAX + 1];
	t_mshctx	msh;
   
	msh = (t_mshctx){0};
	msh.env = our_env;
	while (1)
	{
		env_set(msh.env, "?", ft_itoa(WEXITSTATUS(*exit_status)));
		init_termios();
		signal(SIGINT, handle_sigint);
		if (msh.prompt)
			free(msh.prompt);
		if (line_read)
			free(line_read);
		msh.prompt = ft_strfmt("%s> ", getcwd(buff, PATH_MAX + 1));
		rl_gets(&line_read, msh.prompt);
		if (line_read == NULL || *line_read == '\0')
			continue ;
		reset_termios();
		msh.lst = tlst_create(line_read);
		if (!tlst_syntax_check(msh.lst))
		{
			if (env_get(msh.env, "MSHDBG"))
				tlst_print(msh.lst);
			msh.ast = ast_build(msh.lst);
			if (msh.ast)
			{
				ast_expandall(msh.ast, msh.env);
				line_read = NULL;
				process_ast(msh, &msh.env, exit_status);
				ast_memman(&msh.ast, E_ASTLINK, true);
			}
		}
		tlst_destroy(msh.lst);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env		*our_env;
	static int	exit_status = 1;

	(void)argv;
	(void)argc;
	our_env = malloc(sizeof(t_env));
	create_env(our_env, env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_rl(our_env, &exit_status);
	free_env(our_env, true);
	return (0);
}

// const char* __asan_default_options()
// {
// 	// REMOVE BEFORE EVAL
// 	//return "detect_leaks=0";
// 	return "";
// }
