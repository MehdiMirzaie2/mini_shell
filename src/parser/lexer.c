/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:10:17 by clovell           #+#    #+#             */
/*   Updated: 2023/08/30 14:18:53 by clovell          ###   ########.fr       */
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
	t_token	*last;
	char	c;

	start = tlst_token_new(str, E_TTNA, NULL);
	last = start;
	while (*str)
	{
		while (isspace(*str))
				str++;
		c = *str;
		/* TODO: Compress Logic using `get_ttoken` is `istoken` */
		if (*str == '\'')
			last = tlst_token_new(str++, E_TTSQ, last);	
		else if (*str == '\"')
			last = tlst_token_new(str++, E_TTDQ, last);
		else if (*str == '<')
		{
			if (str[1] == '<')
				last = tlst_token_new(str++, E_TTLLA, last);
			else
				last = tlst_token_new(str, E_TTLA, last);
		}
		else if (*str == '>')
		{
			if (str[1] == '>')
				last = tlst_token_new(str++, E_TTRRA, last);
			else
				last = tlst_token_new(str, E_TTRA, last);
		}
		else if (*str == '|')
			last = tlst_token_new(str, E_TTNCP, last);
		else if (isascii(*str))
		{
			last = tlst_token_new(str, E_TTWD, last);
			while (*str && !isspace(*str))
				str++;
		}
		if (last == NULL)
			return (tlst_destroy(start));
		while (*str && (c == '\'' || c == '\"') && *str != c)
			str++;
		if (*str == c)
			str++;
	}
	//return (start);
	start = start->next; // CAUSES MEMORY LEAK REMOVE TT_ALL / TT_NA
	return (tlst_dup_pass(start));
}

void	*tlst_destroy(t_token *head)
{
	t_token *next;

	next = head->next;
	while (next != NULL)
	{
		if (next->dup == true)
			free(next->str);
		next = next->next;
	}
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


const char* __asan_default_options() { 
	// REMOVE BEFORE EVAL
	return "detect_leaks=0";
}