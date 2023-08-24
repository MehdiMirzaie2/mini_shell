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

// typedef enum e_redirect_type	t_redirect_type;
// enum e_redirect_type
// {
// 	E_PIPE,
// 	E_AND,
// 	E_DAND,
// 	E_OR,
// 	E_DOR
// };
struct s_env
{
	char	*name;
	char	*args;
	t_env	*next;
};

extern int	g_value;

char	*my_strtok(char *srcString, char *delim);

// utils/signals
void handle_sigint(int sig);

// redirections
int redirect_input(const char *filename);
int	redirect_output(const char *filename);

// builtins
void	ft_echo(char *str, char *filename, int option);
void	ft_cd(const char *path);
void	ft_pwd(void);

/* env.c */
/* Creates a new environement variable list */
void    create_env(t_env *our_env, char **env);

/* Return the value of an environement variable.
 * Returns NULL if environement variable doesn't exist.
 */
char	*env_get(t_env *our_env, char *name);
#endif
