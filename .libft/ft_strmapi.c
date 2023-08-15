/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:09:03 by clovell           #+#    #+#             */
/*   Updated: 2023/03/14 14:11:46 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dup;
	size_t	idx;

	dup = ft_strdup(s);
	if (dup == NULL)
		return (NULL);
	idx = 0;
	while (dup[idx] != '\0')
	{
		dup[idx] = f(idx, dup[idx]);
		idx++;
	}
	return (dup);
}
