/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:23:51 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 12:35:24 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

typedef unsigned char	t_uchar;

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				e;
	const t_uchar	*us;
	t_uchar			uc;

	if (n == 0)
		return (0);
	e = n;
	us = (const t_uchar *)s;
	uc = (t_uchar)c;
	while (us[e - n] != uc)
	{
		if (e - n == n - 1)
			return (0);
		e++;
	}	
	return ((void *)&s[e - n]);
}
