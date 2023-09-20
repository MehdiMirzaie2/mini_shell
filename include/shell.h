#ifndef SHELL_H
# define SHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <string.h>

# include "libft.h"
# include "ast.h"
# include "builtins.h"

#define IN dup(STDIN_FILENO)

typedef struct s_vars			t_vars;
typedef struct s_shell			t_shell;
typedef struct s_fd				t_fd;

struct s_fd
{
	int	saved_out_in_fd;
	int	temp_out_in_fd;
};

extern int	g_value;

// main
char *rl_gets(char **line_read, char *header);


char	*my_strtok(char *srcString, char *delim);

// utils/signals
void handle_sigint(int sig);
// void handle_siguser1(int sig);

// redirections
int redirect_input(char *filename);
// int	redirect_output(char *filename);
t_fd	redirect_output(char *filename);

/*
Deletes /tmp/mytempfileXXXXXX which was created for heredoc
*/
void    delete_tempfile(void);

/*
Adds a node to the neivornmefaat ars
*/
void add_node_to_env(t_env **our_env, char *name, char *args);

// void	ft_pwd(void);

/* env.c */
/* Creates a new environement variable list */
void    create_env(t_env *our_env, char **env);
void	free_env(t_env *env);

/* Return the value of an environement variable.
 * Returns NULL if environement variable doesn't exist.
 */
char	*env_get(t_env *our_env, char *name);

/* Sets or creates a new environment variabled named 'key'
 * to the value of 'value' (duplicated)
 */
void	env_set(t_env *our_env, char *key, char *value);

/* expand.c */

/* Expands env vars within the nodes and commands of an ast.
 */
void ast_expandall(t_ast *ast, t_env *env);

/* Expands env vars within the name and args of a command.
 * USEDIN: ast_expandall.
 */
void cmd_expand(t_cmd *cmd, t_env *env);

/* Returns a new string where env vars have been expanded.
 * Expanded string is a new string if the var was found.
 * otherwise it returns 'str'.
 * USEDIN: cmd_expand
 */
char *expand_str(char *str, t_env *env);

/* expand_utils.c */
int until_expandstr_start(char *str, int i);
int until_expandstr_end(char *str, int i);

/* TODO: Remove?
int until_expandstr_start(int c);
int until_expandstr_end(int c);
*/
#endif
