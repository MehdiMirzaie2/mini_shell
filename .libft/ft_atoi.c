/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:54:13 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 15:42:59 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	int	istab;

	istab = (c == '\t' || c == '\v');
	return (c == '\n' || c == '\f' || c == '\r' || c == ' ' || istab);
}

int	ft_atoi(const char *str)
{
	int	negative;
	int	accum;

	accum = 0;
	negative = 1;
	while (ft_isspace(*str))
			str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		accum = accum * 10 + (*str - '0');
		str++;
	}
	return (accum * negative);
}
