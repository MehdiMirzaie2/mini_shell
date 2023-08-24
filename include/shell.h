#ifndef SHELL_H
#define SHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>


// #include "../../lib/include/libft.h"
#include "libft.h"
#include <string.h>
typedef struct s_vars			t_vars;
typedef struct s_cmdtree		t_cmdtree;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
// typedef enum e_redirect_type	t_redirect_type;

// enum e_redirect_type
// {
// 	E_PIPE,
// 	E_AND,
// 	E_DAND,
// 	E_OR,
// 	E_DOR
// };

struct s_cmdtree
{
	t_cmd				*cmd;
	char				*redirect;
	t_cmdtree			*next;
};

struct s_cmd
{
	char	*arg;
	t_cmd	*next;
	// char **redirections;
};

struct s_env
{
	char	*name;
	char	*args;
	t_env	*next;
};

int g_value;

int	process_input(char *input, t_cmdtree *cmdtree);

// utils
void	free_ast(t_cmdtree *cmdtree);
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
#endif
