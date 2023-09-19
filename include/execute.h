#ifndef EXECUTE_H
# define EXECUTE_H

# include "shell.h"

typedef struct s_pipex		t_pipex;
struct s_pipex
{
	t_env	*our_env;
	t_ast	*cmd;
};

t_ast	*get_next_node(t_ast *ast, bool reset);
void	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env);
void	execute_system_cmds(t_cmd *cmd, t_env *env);
int		process_ast(t_ast *ast, t_env **our_env);

// utils
int		get_num_cmd(t_ast *ast);
int	redirect(int from, int to);
// int		re_output(int from, int to);
// int		re_input(int from, int to);
bool	is_builtin(char	*cmd);

#endif