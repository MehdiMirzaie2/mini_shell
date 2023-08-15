/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:00:08 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 16:04:46 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	j;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i + j < len)
	{
		j = 0;
		while (j < needle_len + 1)
		{
			if (i + j > len)
				break ;
			if (needle[j] == '\0')
				return (((char *)haystack) + i);
			if (haystack[i + j] != needle[j] || haystack[i + j] == '\0')
				break ;
			j++;
		}
		i++;
	}
	return (NULL);
}
