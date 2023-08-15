/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:25:39 by clovell           #+#    #+#             */
/*   Updated: 2023/03/29 14:34:59 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

static char	**cleanup(char **indices)
{
	char	**start;

	if (!indices)
		return (NULL);
	start = indices;
	while (*start)
	{
		free(*start);
		start++;
	}
	free(indices);
	return (NULL);
}

/* Copies the content of source into dest by len. */
static void	*strldup(const char *source, size_t len)
{
	char	*dest;

	dest = ft_calloc(len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, source, len + 1);
	return (dest);
}

/* Returns the length of str until the first occurance of end or NULL. */
static size_t	strlenuntil(const char *str, char end)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != end)
		len++;
	return (len);
}

/* Splits the given string up into multiple unique strings based on char 'c'
 * Returns null if memory allocation failed. 
 *
 * Implementation Notes:
 * If the first "word" in stritr is valid, it will immediately emplaces it,
 * Then it will begin to loop through stritr and emplaces the strings
 * A word is anything delimited by a single or contiguous set of 'c'.
 */
static char	**split(const char *stritr, char c, char **indices, size_t size)
{
	size_t	len;

	size = (*stritr != c && *stritr);
	if (size > 0)
	{
		len = strlenuntil(stritr, c);
		indices[0] = strldup(stritr, len);
		if (indices[0] == NULL)
			return (NULL);
	}
	while (*stritr && *(stritr + 1))
	{
		if (*stritr == c && *(stritr + 1) != c)
		{
			size++;
			len = strlenuntil(stritr + 1, c);
			if (len == 0)
				continue ;
			indices[size - 1] = strldup(stritr + 1, len);
			if (indices[size - 1] == NULL)
				return (NULL);
		}
		stritr++;
	}
	return (indices);
}

/* Returns an array of char * or NULL (if memory allocation fails):
 * Each element:
 * Points to the first location of text after single/contiguous end characters.
 * Last element in the array is a NULL pointer.
 */
char	**ft_split(char const *s, char c)
{
	char	**indices;
	size_t	size;
	char	**ind2;
	char	*s1;

	s1 = (char *)s;
	size = (*s != c && *s);
	while (*s1 && *(s1 + 1))
	{
		if (*s1 == c && *(s1 + 1) != c)
			size++;
		s1++;
	}
	indices = (char **)ft_calloc(size + 1, sizeof(char *));
	if (indices == NULL)
		return (NULL);
	else if (size > 0)
	{
		ind2 = split((char *)s, c, indices, 0);
		if (ind2 == NULL || ind2[0] == NULL)
			return (cleanup(indices));
	}
	indices[size] = NULL;
	return (indices);
}
