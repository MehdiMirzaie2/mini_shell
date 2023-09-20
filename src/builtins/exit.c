/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:34:11 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/20 15:13:57 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

void	exiting(int	*value, t_cmd *cmd)
{
	int num_args;
	
	num_args = get_num_args(cmd);
	if (num_args > 2)
	{
		perror("exit: too many arguments");
		*value = 1;
		return ;
	}
	if (num_args == 1)
		*value = ft_atoi(cmd->args->str);
	exit(*value);
}

void	put_exitstatus(int value)
{
	printf("command not found: %d\n", value);
}
