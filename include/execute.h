/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:31:46 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/20 13:32:13 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// void	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env);
void	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env,
			int *exit_status);
void	execute_system_cmds(t_cmd *cmd, t_env *env);
int		process_ast(t_ast *ast, t_env **our_env, int *exit_status);

// utils
int		get_num_cmd(t_ast *ast);
int		get_num_args(t_cmd *cmd);
int		redirect(int from, int to);
bool	is_builtin(char	*cmd);

#endif