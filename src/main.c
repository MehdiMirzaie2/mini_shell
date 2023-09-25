/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mmirzaie  <mmirzaie@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/08 12:50:42 by mmirzaie		  #+#	#+#			 */
/*   Updated: 2023/09/20 15:21:45 by clovell          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"
#include "libft.h"
#include "lexer.h"
#include "ast.h"

int	g_value;

char	*rl_gets(char **line_read, char *header)
{
	if (*line_read)
	{
		free(*line_read);
		*line_read = NULL;
	}
	*line_read = readline(header);
	free(header);
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
	t_ast		*ast;
	static char	*line_read = NULL;
	char		buff[PATH_MAX + 1];
	t_token		*lst;

	ast = NULL;
	while (1)
	{
		env_set(our_env, "?", ft_itoa(WEXITSTATUS(exit_status)));
		rl_gets(&line_read, ft_strfmt("%s> ", getcwd(buff, PATH_MAX + 1)));
		lst = tlst_create(line_read);
		ast = ast_build(lst);
		ast_expandall(ast, our_env);
		line_read = NULL;
		process_ast(ast, &our_env, exit_status);
		tlst_destroy(lst);
		ast_memman(&ast, 0, true);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env		*our_env;
	static int	exit_status = 0;

	(void)argc;
	(void)argv;
	our_env = malloc(sizeof(t_env));
	create_env(our_env, env);
	signal(SIGINT, handle_sigint);
	signal(SIGUSR1, handle_sigint);
	init_rl(our_env, &exit_status);
	free_env(our_env);
	return (0);
}

// const char* __asan_default_options()
// {
// 	// REMOVE BEFORE EVAL
// 	//return "detect_leaks=0";
// 	return "";
// }
