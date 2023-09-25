/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:43:28 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/25 20:21:06 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_extra.h"

void	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env,
	int *exit_status)
{
	if (ft_strncmp(cmd_struct->cmd, "cd", 2) == 0)
		ft_cd(cmd_struct, our_env);
	else if (ft_strncmp(cmd_struct->cmd, "env", 3) == 0)
		ft_env(*our_env);
	else if (ft_strncmp(cmd_struct->cmd, "export", 6) == 0)
		ft_export(our_env, cmd_struct->args->str);
	else if (ft_strncmp(cmd_struct->cmd, "echo", 4) == 0)
		ft_echo(cmd_struct);
	else if (ft_strncmp(cmd_struct->cmd, "unset", 5) == 0)
		unset(*our_env, cmd_struct->args->str);
	else if (ft_strncmp(cmd_struct->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd_struct->cmd, "exit", 4) == 0)
		exiting(exit_status, cmd_struct);
}
