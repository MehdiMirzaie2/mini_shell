/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:31:46 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/12 15:39:52 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "shell.h"

typedef struct s_pipex		t_pipex;
typedef enum e_permissions	t_permissions;
struct s_pipex
{
	t_env	*our_env;
	t_ast	*cmd;
};

enum e_permissions
{
	E_IN = O_RDONLY,
	E_OUT = O_WRONLY | O_CREAT | O_TRUNC,
	E_APPEND = O_WRONLY | O_CREAT | O_APPEND,
};

void	execute(t_ast *ast, t_env **our_env, int *exit_status, int num_cmds);
void	open_file(t_ast *ast, int pipe1[2], int num_cmds);

t_ast	*get_next_node(t_ast *ast, int num_cmds);
void	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env,
			int *exit_status);
void	execute_system_cmds(t_cmd *cmd, t_env *env);
void	process_ast(t_mshctx msg, t_env **our_env, int *exit_status);
// void	handle_heredoc(t_ast *ast);
void	handle_heredoc(t_iolst *redirects);
void	error_exit(char *error, int val);

// utils
int		get_num_cmd(t_ast *ast);

/*
gets the number of args inside a command structure
*/
int		get_num_args(t_cmd *cmd);

/*
using dup2 it will redirect from "from" to "to", and close "from";
*/
int		redirect(int from, int to);

bool	is_builtin(t_cmd	*cmd);

/*
same as is_builtin but it checks if the cmd will change the env;
*/
bool	is_envbuiltin(t_cmd	*cmd);

char	**join_cmd(t_cmd *cmd);
char	*ft_cmdcat(char *path, char *cmd);
char	*cmd_path(char **splitted_paths, char *cmd);

#endif
