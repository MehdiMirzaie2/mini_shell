/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:43:28 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/14 17:58:44 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_extra.h"

int	execute_builtin_cmds(t_cmd *cmd, t_env **our_env)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		status = ft_cd(cmd, our_env);
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ft_env(*our_env);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		status = ft_export(our_env, cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		status = unset(our_env, cmd->args);
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		exiting(cmd);
	return (status);
}
