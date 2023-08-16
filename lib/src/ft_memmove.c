/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:56:50 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/13 15:35:28 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// line 27
// typecasting dst and src with (size_t) so we can compare them with len
// checking to see if dst and src overlap 
// if they do len will be larger than the difference
// if that happens we copy from the end of src

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	if ((size_t)dst - (size_t)src < len)
	{
		i = len - 1;
		while (i >= 0 && i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}
