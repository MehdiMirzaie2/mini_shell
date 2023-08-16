/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:25:32 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/16 13:44:59 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	c;
	int	s;
	int	res;

	c = 0;
	s = 1;
	res = 0;
	while (str[c] == ' ' || str[c] == '\n' || str[c] == '\t'
		|| str[c] == '\v' || str[c] == '\f' || str[c] == '\r')
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			s = -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (res * 10) + (str[c] - '0');
		c++;
	}
	return (res * s);
}
// #include <stdio.h>
// int main(void)
// {
// 	// printf("%d", ft_atoi("\t\n\r\v\f  469 \n"));
// 	// char *n = "\t\v\f\r\n\e \f-06050";
// 	char *n = "+-45";
// 	int i1 = atoi(n);
// 	int i2 = ft_atoi(n);
// 	printf("%d\n", i1);
// 	printf("%d\n", i2);
// 	return(0);
// }
