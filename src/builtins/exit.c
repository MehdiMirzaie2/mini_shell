/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:34:11 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/05 14:05:56 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

void	exiting(int	*value, t_cmd *cmd)
{
	int	num_args;

	num_args = get_num_args(cmd);
	if (num_args >= 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		*value = 1;
	}
	if (num_args == 1)
	{
		if (ft_isalpha(*cmd->args->str))
		{
			write(2, "exit: ", 6);
			ft_putstr_fd(cmd->args->str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			*value = 255;
		}
		else
			*value = ft_atoi(cmd->args->str);
	}
	exit(*value);
}
