/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:55:29 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 16:03:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	end;
	size_t	begin;
	size_t	i;

	begin = ft_strlen(dest);
	end = ft_strlen(src);
	i = 0;
	while (i < end && i + begin + 1 < dstsize)
	{
		dest[begin + i] = src[i];
		i++;
	}
	if (dstsize < begin)
		begin = dstsize;
	else
		dest[begin + i] = '\0';
	return (begin + end);
}
