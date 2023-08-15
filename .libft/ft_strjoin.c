/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:11:49 by clovell           #+#    #+#             */
/*   Updated: 2023/03/09 17:19:45 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{	
	size_t	s1len;
	size_t	s2len;
	char	*dst;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dst = malloc(s1len + s2len + 1);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s1, s1len);
	ft_strlcpy(dst + s1len, s2, s2len + 1);
	return (dst);
}
