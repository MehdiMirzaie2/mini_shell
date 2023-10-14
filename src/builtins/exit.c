/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:34:11 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/14 14:59:30 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

void	exiting(t_cmd *cmd)
{
	int				num_args;
	long long int	str_to_int;
	double			checker;
	char			*number;

	num_args = get_num_args(cmd);
	if (num_args == 0)
		exit(0);
	number = cmd->args->str;
	if (!ft_str_isnum(number))
		exit(ft_printf_fd(2, "exit: %s: numeric argument required\n",
				number) + 254);
	else if (num_args >= 2)
		exit(ft_printf_fd(2, "exit: too many arguments\n"));
	else
	{
		while (*number == ' ')
			++number;
		str_to_int = ft_atol(number);
		checker = ft_atod(number);
		if ((double)str_to_int != checker)
			exit(ft_printf_fd(2, "exit: %s: numeric argument required\n",
					cmd->args->str) + 254);
		exit(str_to_int % 256);
	}
}
