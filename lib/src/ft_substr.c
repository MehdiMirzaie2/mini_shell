/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:50:12 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/15 15:48:26 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	idx;
	size_t	s_len;
	size_t	sub_len;
	char	*sub_str;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	sub_str = malloc(sizeof(char) * (sub_len + 1));
	if (!sub_str)
		return (NULL);
	idx = 0;
	while (idx < sub_len)
		sub_str[idx++] = s[start++];
	sub_str[idx] = '\0';
	return (sub_str);
}
