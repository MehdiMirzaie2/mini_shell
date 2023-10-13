/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:34:11 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/13 17:08:47 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

void	exiting(int	exit_code, t_cmd *cmd)
{
	int	num_args;

	num_args = get_num_args(cmd);
	if (num_args >= 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_code = 1;
	}
	if (num_args == 1)
	{
		if (ft_isalpha(*cmd->args->str))
		{
			write(2, "exit: ", 6);
			ft_putstr_fd(cmd->args->str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_code = 255;
		}
		else
		{
			exit_code = ft_atol(cmd->args->str);
			if (exit_code > 2147483647 || exit_code < -2147483648)
				error_exit(" numeric argument required", 255);
		}
	}
	exit(exit_code);
}
