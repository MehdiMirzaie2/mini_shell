/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:01:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/16 13:43:53 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*convert;
	char	character;

	convert = (char *)s;
	character = (char)c;
	i = ft_strlen(convert);
	while (i >= 0)
	{
		if (convert[i] == character)
			return (&convert[i]);
		i--;
	}
	return (0);
}
