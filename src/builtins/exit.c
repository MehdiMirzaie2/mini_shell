/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:34:11 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/17 10:49:07 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

void	parse_sign(const char *str, int *sign, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		*i += 1;
	}
	else
		*sign = 1;
}

bool	max_min(long long int result, int digit, int sign)
{
	if (sign == -1)
	{
		if (((result * -1) < LLONG_MIN / 10)
			|| (((result * -1) == LLONG_MIN / 10)
				&& ((digit * sign) < LLONG_MIN % 10)))
			return (true);
	}
	else
		if ((result > LLONG_MAX / 10)
			|| ((result == LLONG_MAX / 10) && (digit > LLONG_MAX % 10)))
			return (true);
	return (false);
}

void	ft_atoll(const char *str, long long int *result)
{
	int				sign;
	int				i;
	int				digit;

	i = ft_iterspace(str);
	parse_sign(str, &sign, &i);
	while (str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9'))
		{
			digit = str[i] - '0';
			if (max_min(*result, digit, sign))
				exit(ft_printf_fd(2,
						"exit: %s: numeric argument required\n", str) + 255);
			*result = *result * 10 + digit;
		}
		else if (ft_isspace(str[i]))
			break ;
		else
			exit(ft_printf_fd(2,
					"exit: %s: numeric argument required\n", str) + 1);
		i++;
	}
	*result = *result * sign;
}

int	exiting(t_cmd *cmd)
{
	int				num_args;
	long long int	result;
	char			*number;

	result = 0;
	num_args = get_num_args(cmd);
	if (num_args == 0)
		exit(0);
	number = cmd->args->str;
	if (!ft_str_isnum(number))
		exit(ft_printf_fd(2, "exit: %s: numeric argument required\n",
				number) + 255);
	else if (num_args >= 2)
		return (ft_printf_fd(2, "exit: too many arguments\n") + 256);
	else
	{
		while (*number == ' ')
			++number;
		ft_atoll(number, &result);
		exit(result % 256);
	}
}
