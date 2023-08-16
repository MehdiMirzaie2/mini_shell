/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:51:15 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/13 11:18:12 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (temp == NULL)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[i + j] = '\0';
	return (temp);
}
