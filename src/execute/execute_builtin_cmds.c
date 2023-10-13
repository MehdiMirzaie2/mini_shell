/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:43:28 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/13 17:15:12 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_extra.h"

int	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env)
{
	int status;

	status = 0;
	if (ft_strncmp(cmd_struct->cmd, "cd", 2) == 0)
		status = ft_cd(cmd_struct, our_env);
	else if (ft_strncmp(cmd_struct->cmd, "env", 3) == 0)
		ft_env(*our_env);
	else if (ft_strncmp(cmd_struct->cmd, "export", 6) == 0)
		status = ft_export(our_env, cmd_struct->args);
	else if (ft_strncmp(cmd_struct->cmd, "unset", 5) == 0)
		status = unset(our_env, cmd_struct->args);
	else if (ft_strncmp(cmd_struct->cmd, "echo", 4) == 0)
		ft_echo(cmd_struct);
	else if (ft_strncmp(cmd_struct->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd_struct->cmd, "exit", 4) == 0)
		exiting(status, cmd_struct);
	return (status);
}
