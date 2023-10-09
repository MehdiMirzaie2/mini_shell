/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:10:17 by clovell           #+#    #+#             */
/*   Updated: 2023/10/09 16:42:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft_extra.h"
#include "libft.h"
#include "lexer.h"

t_token	*tlst_create(char *str)
{
	t_token		*start;
	t_token		*tmp;
	t_ttoken	token;
	char		c;

	start = tlst_token_new(str, E_TTNA, NULL);
	tmp = start;
	while (*str)
	{
		while (isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		c = *str;
		token = get_ttoken(str);
		tmp = tlst_token_new(str, token, tmp);
		str = tokstr_advance(str, c, false);
	}
	tmp = start->next;
	free(start);
	return (tlst_dup_pass(tmp));
}

char	*tokstr_advance(char *str, char c, bool quoted)
{
	int		i;
	char	depth;

	if (quoted)
		depth = c;
	else
		depth = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	i = iter_strdupctx(str, NULL, &depth, sd_until_arg_end);
	return (&str[i]);
}

t_sd_stat	sd_until_arg_end(char *str, int i, bool check, void *pctx)
{
	char *const	depth = pctx;

	if (str[i] == '\0')
		return (E_SD_STOP);
	if (str[i] == '\"' || str[i] == '\'')
	{
		if (depth[check] == '\0')
			depth[check] = str[i];
		else if (depth[check] == str[i])
			depth[check] = '\0';
	}
	else if (depth[check] != '\0')
		return (E_SD_COPY);
	if (ft_isspace(str[i]))
		return (E_SD_STOP);
	else if ((str[i] == '<' || str[i] == '>') && \
			((get_ttoken(&str[i + 1]) & E_TTLR) == 0))
		return (E_SD_STOP | E_SD_COPY);
	else if (str[i] == '|')
			return (E_SD_STOP | ((i == 0) * E_SD_COPY));
	return (E_SD_COPY);
}

t_token	*tlst_dup_pass(t_token *head)
{
	t_token	*next;
	char	lstr[2];
	char	depth[2];

	lstr[1] = '\0';
	next = head;
	while (next != NULL)
	{
		depth[0] = '\0';
		depth[1] = '\0';
		lstr[0] = next->str[0];
		if ((next->type & (E_TTGS | E_TTWD)) != 0)
			next->str = ft_strdupctx(next->str, depth, sd_until_arg_end);
		else
			next->str = ft_strdup(lstr);
		if (next->str == NULL)
			return (tlst_destroy(head));
		else if (next->type != E_TTNA)
			next->dup = true;
		next = next->next;
	}
	return (head);
}
