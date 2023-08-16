/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:01:03 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/14 16:44:44 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx;

	if (*needle == '\0')
		return ((char *)haystack);
	idx = ft_strlen((char *)needle);
	while (*haystack != '\0' && len-- >= idx)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, idx) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
