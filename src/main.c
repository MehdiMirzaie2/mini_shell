/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mmirzaie  <mmirzaie@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/08 12:50:42 by mmirzaie		  #+#	#+#			 */
/*   Updated: 2023/09/11 01:46:45 by clovell          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "shell.h"


int	g_value;

// we need to take care of exit status
// other people use the global variable for this.
#include "libft.h"
#include "lexer.h"
#include "ast.h"

char *rl_gets(char **line_read, char *header)
{
	/* If the buffer has already been allocated, return the memory
		to the free pool. */
	if (*line_read)
	{
		free(*line_read);
		*line_read = NULL;
	}
	/* Get a line from the user. */
	*line_read = readline(header); 
	// SHOULD WE FERE HEADER, Do some tests.
	free(header);
	// this takes care of control d, needs to free mem.
	if (!(*line_read))
	{
		printf("control d\n");
		exit(EXIT_SUCCESS);
	}
	/* TODO: Handle quote modes */
	/* If the line has any text in it, save it on the history. */
	if (*line_read && **line_read)
		add_history(*line_read);
	return *line_read;
	/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
}
// void print_tokenlst(t_token *start);
// void tast_print(t_ast *ast);


int main(int argc, char **argv, char **env)
{
	/* A static variable for holding the line. */
	t_ast		*ast;
	t_env		*our_env;
	static char *line_read  = NULL;
	char	buff[PATH_MAX + 1];

	(void)argc;
	(void)argv;
	our_env = malloc(sizeof(t_env));
	ast = NULL;

	create_env(our_env, env);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (1)
	{
		printf("%d\n", g_value);
		if (g_value == SIGINT)
			exit(EXIT_FAILURE);
		rl_gets(&line_read, ft_strfmt("%s> ", getcwd(buff, PATH_MAX + 1))); // Pass the pointer by reference
		if (ft_strncmp("exit", line_read, 4) == 0)
		{
			free_env(our_env);
			exit(EXIT_SUCCESS);
		}
		if (line_read[0] == '#' && line_read[1] == '1') // For testing purposes
			line_read = ft_strdup("cat << EOF > file | wc -c | tr -d " " > file");
		if (line_read[0] == '#' && line_read[1] == '2' ) // For testing purposes
			line_read = ft_strdup("   \techo \t\"test \'(quote)\'\" \'sq\' <less | tr -r | awk '{printf $0}' | (first (second) (third (forth)))");
		// Do something with line_read, if needed
		t_token *lst = tlst_create(line_read);
		ast = ast_build(lst);
		tast_print(ast);
		// tlst_print(lst);
		if (ast->type == E_ASTCMD && ast->u_node.cmd && ast->u_node.cmd->cmd)
		{
			ast_expandall(ast, our_env);
			tast_print(ast);
			t_cmd *cmd =	ast->u_node.cmd;
			char *path;
			if (ast->u_node.cmd->args == NULL)
				path = NULL;
			else
				path = ast->u_node.cmd->args->str;
			//	int inargc;
			//	char **inargv = strlstarray(cmd->args, &argc);
			if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
				ft_cd(path, &our_env);
			else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
				ft_env(our_env);
			else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
				export(our_env, path);
			else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
			{
				 if (ast->u_node.cmd->strout == NULL)
					 ft_echo(path, NULL, 0);
				else
					 ft_echo(path, ast->u_node.cmd->strout->str, 0);
			}
			else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
				unset(our_env, path);
			else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
				ft_pwd();
			//free_darray(inargv, argv);
		}
		// take care of the signals in this part.
		// Free the memory after you're done using it
		tlst_destroy(lst);
		ast_memman(&ast, 0, true);
	}
	free_env(our_env);
	return (0);
}

const char* __asan_default_options() { 
	// REMOVE BEFORE EVAL
	//return "detect_leaks=0";
	return "";
}
