/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:10:17 by clovell           #+#    #+#             */
/*   Updated: 2023/10/13 16:35:48 by clovell          ###   ########.fr       */
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
		while (ft_isspace(*str))
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

t_sd_stat	sd_until_arg_end(char *s, int i, bool check, void *pctx)
{
	const bool	arrow = s && (s[i] == '>' || s[i] == '<');
	const bool	arrow_next = s && *s && (s[i + 1] == '>' || s[i + 1] == '<');

	if (s[i] == '\0')
		return (E_SD_STOP);
	if (s[i] == '\"' || s[i] == '\'')
	{
		if (((char *)pctx)[check] == '\0')
			((char *)pctx)[check] = s[i];
		else if (((char *)pctx)[check] == s[i])
			((char *)pctx)[check] = '\0';
	}
	if (((char *)pctx)[check] != '\0')
		return (E_SD_COPY);
	if (ft_isspace(s[i]))
		return (E_SD_STOP);
	else if (arrow && arrow_next && s[i] != s[i + 1])
		return (E_SD_STOP | E_SD_COPY);
	else if (arrow && ((get_ttoken(&s[i + 1]) & E_TTLR) == 0))
		return (E_SD_STOP | E_SD_COPY);
	else if (!arrow && arrow_next)
		return (E_SD_COPY | E_SD_STOP);
	else if (s[i] == '|')
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
