#ifndef SHELL_H
#define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_shell t_shell;
typedef struct s_vars t_vars;

struct s_vars
{
	int	hash;
	char *key;
	char *value;

	t_vars *next;
};

struct s_cmd_list
{
	char *cmd;
	t_cmd_list *next;
}

t_cmd_list *get_cmd(t_cmd_list *head, char * key);
char *get_env(t_vars *head, char *key);
void add_env(t_vars *vars, char *key, char *value);

typedef struct s_shell {
	t_vars	env;
	char *cd_path;
	t_cmd_list list;
	int			current_cmd;
	char **path;
	///usr/bin
	///bin
	//..
	//NULL
} t_shell;

#endif
