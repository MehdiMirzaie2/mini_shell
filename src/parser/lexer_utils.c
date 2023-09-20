/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:21:50 by clovell           #+#    #+#             */
/*   Updated: 2023/09/16 02:59:44 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "lexer.h"
#include "libft.h"
#include "libft_extra.h"

t_ttoken	get_ttoken(char *str)
{
	char			*fnd;
	const char		*list = "\'\"|<>";
	const t_ttoken	types[] = {
		E_TTSQ, E_TTDQ, E_TTNCP, E_TTLA, E_TTRA,
	};

	if (str == NULL || *str == '\0')
		return (E_TTNA);
	else if (str[0] == '<' && str[1] == '<')
		return (E_TTLLA);
	else if (str[0] == '>' && str[1] == '>')
		return (E_TTRRA);
	fnd = ft_strchr(list, str[0]);
	if (fnd != NULL)
		return (types[fnd - list]);
	return (E_TTWD);
}

bool	istok_advancable(t_ttoken tok)
{
	const t_ttoken	adv[] = {
		E_TTSQ, E_TTDQ, E_TTLLA, E_TTRRA,
	};
	unsigned int	i;

	i = 0;
	while (i < sizeof adv)
	{
		if (tok == adv[i++])
			return (true);
	}
	return (false);
}

char	*tokstr_advance(char *str, char c, bool quoted)
{
	if (quoted)
	{
		while (*str && (c == '\'' || c == '\"') && *str != c)
			str++;
		if (*str == c)
			str++;
	}
	else
	{
		while (*str && !ft_isspace(*str))
			str++;
	}
	return (str);
}
