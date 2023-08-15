/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:13:50 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 12:31:09 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int			i;
	char		*cdst;
	const char	*csrc;

	cdst = (char *)dst;
	csrc = (const char *)src;
	if (cdst <= csrc || cdst >= csrc + len)
		return (ft_memcpy(dst, (void *)src, len));
	i = 1;
	while (1)
	{
		cdst[len - i] = csrc[len - i];
		if (len - i == 0)
			break ;
		i++;
	}
	return (dst);
}
