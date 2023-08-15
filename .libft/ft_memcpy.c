/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:55 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 16:07:21 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t	idx;

	if (dst == NULL && src == NULL)
		return (NULL);
	idx = 0;
	while (idx < size)
	{
		((char *)dst)[idx] = ((char *)src)[idx];
		idx++;
	}
	return (dst);
}
