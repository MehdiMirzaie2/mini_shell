/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:34:11 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/14 23:07:40 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// long long int ft_atod(const char *str);

long long int ft_atod(const char *str)
{
    long long int result = 0;
    int sign = 1;
    int i = 0;

	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
    while (str[i] != '\0')
	{
        if ((str[i] >= '0' && str[i] <= '9'))
		{
            int digit = str[i] - '0';
			if (sign == -1)
			{
				if (((result * -1) < LLONG_MIN / 10) || (((result * -1) == LLONG_MIN / 10) && ((digit * sign) < LLONG_MIN % 10)))
				{
                	fprintf(stderr, "exit: %s: numeric argument required\n", str);
                	exit(255);
				}
			}
			else
			{
				if ((result > LLONG_MAX / 10) || ((result == LLONG_MAX / 10) && (digit > LLONG_MAX % 10)))
				{
					fprintf(stderr, "exit: %s: numeric argument required\n", str);
					exit(255);
				}
            }
            result = result * 10 + digit;
        }
		else if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
			return (result * sign);		
		else {
            fprintf(stderr, "exit: %s: numeric argument required\n", str);
            exit(1);
        }
        i++;
    }
    return (result * sign);
}

void	exiting(t_cmd *cmd)
{
	int				num_args;
	long long int	str_to_int;
	char			*number;

	num_args = get_num_args(cmd);
	if (num_args == 0)
		exit(0);
	number = cmd->args->str;
	if (!ft_str_isnum(number))
		exit(ft_printf_fd(2, "exit: %s: numeric argument required\n",
				number) + 255);
	else if (num_args >= 2)
		exit(ft_printf_fd(2, "exit: too many arguments\n") + 1);
	else
	{
		while (*number == ' ')
			++number;
		str_to_int = ft_atod(number);
		exit(str_to_int % 256);
	}
}


// void	exiting(t_cmd *cmd)
// {
// 	int				num_args;
// 	long long int	str_to_int;
// 	double			checker;
// 	char			*number;

// 	num_args = get_num_args(cmd);
// 	if (num_args == 0)
// 		exit(0);
// 	number = cmd->args->str;
// 	if (!ft_str_isnum(number))
// 		exit(ft_printf_fd(2, "exit: %s: numeric argument required\n",
// 				number) + 255);
// 	else if (num_args >= 2)
// 		exit(ft_printf_fd(2, "exit: too many arguments\n"));
// 	else
// 	{
// 		while (*number == ' ')
// 			++number;
// 		str_to_int = ft_atol(number);
// 		checker = ft_atod(number);
// 		if ((double)str_to_int != checker)
// 			exit(ft_printf_fd(2, "exit: %s: numeric argument required\n",
// 					cmd->args->str) + 255);
// 		exit(str_to_int % 256);
// 	}
// 	LONG_MAX;
// }
