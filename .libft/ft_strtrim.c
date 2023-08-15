/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:27:13 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 20:19:33 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

/* Returns 1 if the char 'c' is contained in 'set'.*/
static int	contains(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

/* Returns the amount of found characters from set in contiguous space,
 * at the start of s1 or from the back of s1 (if len is 0).*/
static unsigned int	count_removal(const char *s1, const char *set, size_t len)
{
	size_t	i;

	i = 0;
	if (len > 0)
	{
		while (s1[len - i - 1] && contains(s1[len - i - 1], set))
		{
			i++;
		}
	}		
	else
	{
		while (s1[i] && contains(s1[i], set))
		{
			i++;
		}
	}
	return (i);
}

/* Remove any occurance of set from the start of s1 and the endk of s1, 
 * start and end are defined as when the first and last occurances of any 'set'
 *  character is found plus / minus 1*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	end;
	size_t	start;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	end = count_removal(s1, set, s1_len);
	start = count_removal(s1, set, 0);
	if (start == s1_len || end == s1_len)
		return (ft_strdup(""));
	dst = malloc((s1_len - start) - end + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1 + start, (s1_len - start) - end + 1);
	return (dst);
}
