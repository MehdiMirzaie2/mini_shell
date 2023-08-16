/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:42:56 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/16 14:32:02 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	fill_others(int size, int offset, int n, char *ret_chars)
{
	while (size > offset)
	{
		ret_chars[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	int		offset;
	int		size;
	char	*ret_chars;

	offset = 0;
	size = get_size(n);
	ret_chars = (char *)malloc(sizeof(char) * size + 1);
	if (!ret_chars)
		return (0);
	if (n == -2147483648)
	{
		ret_chars[0] = '-';
		ret_chars[1] = '2';
		n = 147483648;
		offset = 2;
	}
	if (n < 0)
	{
		ret_chars[0] = '-';
		offset = 1;
		n = -n;
	}
	fill_others(size, offset, n, ret_chars);
	ret_chars[size] = '\0';
	return (ret_chars);
}
