/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:43:28 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/16 11:33:12 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft_extra.h"

void	execute_builtin_cmds(t_cmd *cmd_struct, t_env **our_env)
{
	if (ft_strncmp(cmd_struct->cmd, "$?", 2) == 0)
		printf("command not found %d", errno);
	if (ft_strncmp(cmd_struct->cmd, "cd", 2) == 0)
		ft_cd(cmd_struct->args->str, our_env);
	else if (ft_strncmp(cmd_struct->cmd, "env", 3) == 0)
		ft_env(*our_env);
	else if (ft_strncmp(cmd_struct->cmd, "export", 6) == 0)
		export(our_env, cmd_struct->args->str);
	// else if (ft_strncmp(cmd_struct->cmd, "echo", 4) == 0)
	// {
	// 	if (cmd_struct->strout == NULL)
	// 		ft_echo(cmd_struct->args->str, NULL, 0);
	// 	else
	// 		ft_echo(cmd_struct->args->str, cmd_struct->strout->str, 0);
	// }
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
}
