/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:43:28 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/20 12:43:45 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_extra.h"

void	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env, int *exit_status)
{
	if (ft_strncmp(cmd_struct->cmd, "$?", 2) == 0)
		put_exitstatus(*exit_status);
	if (ft_strncmp(cmd_struct->cmd, "cd", 2) == 0)
		ft_cd(cmd_struct->args->str, our_env);
	else if (ft_strncmp(cmd_struct->cmd, "env", 3) == 0)
		ft_env(*our_env);
	else if (ft_strncmp(cmd_struct->cmd, "export", 6) == 0)
		ft_export(our_env, cmd_struct->args->str);
	else if (ft_strncmp(cmd_struct->cmd, "echo", 4) == 0)
	{
		if (cmd_struct->strout == NULL)
			ft_echo(cmd_struct->args, NULL);
		else
			ft_echo(cmd_struct->args, cmd_struct->strout->str);
	}
	else if (ft_strncmp(cmd_struct->cmd, "unset", 5) == 0)
		unset(*our_env, cmd_struct->args->str);
	else if (ft_strncmp(cmd_struct->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd_struct->cmd, "exit", 4) == 0)
		exiting(exit_status, cmd_struct);
}
