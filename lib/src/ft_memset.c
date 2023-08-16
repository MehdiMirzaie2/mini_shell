/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:09:11 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/13 10:43:05 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	chr;

	ptr = s;
	chr = c;
	i = 0;
	while (i < len)
	{
		ptr[i] = chr;
		i++;
	}
	return (s);
}
