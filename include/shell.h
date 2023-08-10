#ifndef SHELL_H
#define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_vars t_vars;
typedef struct s_cmdtree t_cmdtree;
typedef struct s_cmd	t_cmd;
typedef enum e_pipetype	t_pipetype;

enum e_pipetype
{
	E_PIPE,
	E_AND,
	E_DAND,
	E_OR,
	E_DOR
};

struct s_cmdtree
{
	t_cmd *left;
	t_cmd *right;
	t_pipetype type;

	t_cmdtree *next;
};

struct s_cmd
{
	char **args;
	char ** redirections;
};


// t_cmdtree create_cmdtree(char *line);

// void		execute_cmdtree(t_cmdtree *tree);


int	process_input(char *input);

#endif
