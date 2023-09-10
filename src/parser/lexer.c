/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:10:17 by clovell           #+#    #+#             */
/*   Updated: 2023/09/07 02:01:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft_extra.h"
#include "libft.h"
#include "lexer.h"

t_ttoken	get_ttoken(char *str)
{
	char			*fnd;
	const char		*list = "\'\"|<>";
	const t_ttoken	types[] = 
	{
		E_TTSQ, E_TTDQ, E_TTLA, E_TTRA,
		E_TTLLA, E_TTRRA, E_TTNCP
	};

	if (str == NULL || *str)
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

t_token	*tlst_token_new(char *str, t_ttoken type, t_token *parent)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	while (parent != NULL && parent->next != NULL)
		parent = parent->next;
	if (parent != NULL)
		parent->next = token;
	return (token);
}

t_token	*tlst_create(char *str)
{
	t_token	*start;
	t_token	*tmp;
	char	c;

	start = tlst_token_new(str, E_TTNA, NULL);
	tmp = start;
	while (*str)
	{
		while (isspace(*str))
				str++;
		c = *str;
		/* TODO: Compress Logic using `get_ttoken` is `istoken` */
		if (*str == '\'')
			tmp = tlst_token_new(str++, E_TTSQ, tmp);	
		else if (*str == '\"')
			tmp = tlst_token_new(str++, E_TTDQ, tmp);
		else if (*str == '<')
		{
			if (str[1] == '<')
				tmp = tlst_token_new(str++, E_TTLLA, tmp);
			else
				tmp = tlst_token_new(str, E_TTLA, tmp);
		}
		else if (*str == '>')
		{
			if (str[1] == '>')
				tmp = tlst_token_new(str++, E_TTRRA, tmp);
			else
				tmp = tlst_token_new(str, E_TTRA, tmp);
		}
		else if (*str == '|')
			tmp = tlst_token_new(str, E_TTNCP, tmp);
		else if (isascii(*str))
		{
			tmp = tlst_token_new(str, E_TTWD, tmp);
			while (*str && !isspace(*str))
				str++;
		}
		if (tmp == NULL)
			return (tlst_destroy(start));
		while (*str && (c == '\'' || c == '\"') && *str != c)
			str++;
		if (*str == c)
			str++;
	}
	tmp = start->next;
	free(start);
	return (tlst_dup_pass(tmp));
}

void	*tlst_destroy(t_token *token)
{
	if (token == NULL)
		return (NULL);
	tlst_destroy(token->next);
	if (token->dup == true)
		free(token->str);
	free(token);
	return (NULL);
}

int	tlst_token_dup(char *str, int i)
{
	if (str[i] == '\0')
			return (2);
	if (str[0] == '\"' || str[0] == '\'')
	{
		if (i > 0 && str[0] == str[i])
			return (2);
		else if (str[0] == str[i])
			return (0);
	}
	else if (ft_isspace(str[i]))
		return (2);
	return (1);
}

t_token	*tlst_dup_pass(t_token *head)
{
	t_token *next;
	char lstr[2];
	
	lstr[1] = '\0';
	next = head;
	while (next != NULL)
	{
		lstr[0] = next->str[0];
		if ((next->type & (E_TTGS | E_TTWD)) != 0)
			next->str = ft_strdupi(next->str, tlst_token_dup);
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


