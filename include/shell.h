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

// #include "../../lib/include/libft.h"
# include "libft.h"
typedef struct s_vars			t_vars;
typedef struct s_env			t_env;
typedef struct s_shell			t_shell;
typedef struct s_fd				t_fd;

struct s_fd
{
	int	saved_out_in_fd;
	int	temp_out_in_fd;
};
struct s_env
{
	char	*name;
	char	*args;
	t_env	*next;
};

extern int	g_value;

// main
char *rl_gets(char **line_read, char *header);


char	*my_strtok(char *srcString, char *delim);

// utils/signals
void handle_sigint(int sig);

// redirections
int redirect_input(char *filename);
// int	redirect_output(char *filename);
t_fd	redirect_output(char *filename);
// builtins
void	ft_cd(char *path, t_env **our_env);
void	ft_env(t_env *our_env);
void	export(t_env *our_env, char *args);
void	ft_echo(char *str, char *filename, int option);
void	unset(t_env *our_env, char *name);
void	ft_pwd(void);


void add_node_to_env(t_env **our_env, char *name, char *args);

// void	ft_pwd(void);

/* env.c */
/* Creates a new environement variable list */
void    create_env(t_env *our_env, char **env);

/* Return the value of an environement variable.
 * Returns NULL if environement variable doesn't exist.
 */
char	*env_get(t_env *our_env, char *name);
#endif
