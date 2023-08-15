/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:20:49 by clovell           #+#    #+#             */
/*   Updated: 2023/03/14 14:08:08 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	ft_itoa_rec(char *dst, int size, long long int n)
{
	if (n == 0 || size < 0)
		return ;
	ft_itoa_rec(dst, size - 1, n / 10);
	dst[size] = n % 10 + '0';
}

static int	nb_len(long long nb)
{
	int	count;

	count = 1;
	nb /= 10;
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long long	ni;
	int			count;
	char		*str;

	ni = n;
	count = nb_len(ni);
	if (n < 0)
		ni = 0L - n;
		str = ft_calloc(count + 1 + (n < 0), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	ni = n;
	if (n < 0)
		ni = 0L - n;
	ft_itoa_rec(str + (n < 0), count - 1, ni);
	if (n < 0)
		str[0] = '-';
	return (str);
}
