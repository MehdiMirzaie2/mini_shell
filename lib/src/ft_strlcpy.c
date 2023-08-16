/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:00:34 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/14 11:26:20 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t l)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < l)
	{
		dest[i] = src[i];
		i++;
	}
	if (l)
		dest[i] = '\0';
	return (ft_strlen(src));
}
