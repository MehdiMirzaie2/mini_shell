/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:21:50 by clovell           #+#    #+#             */
/*   Updated: 2023/10/13 10:39:51 by clovell          ###   ########.fr       */
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
		E_TTWD, E_TTWD, E_TTNCP, E_TTLA, E_TTRA,
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

t_token	*tlst_token_new(char *str, t_ttoken type, t_token *parent)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	ft_assert(token == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
	token->str = str;
	token->type = type;
	token->next = NULL;
	while (parent != NULL && parent->next != NULL)
		parent = parent->next;
	if (parent != NULL)
		parent->next = token;
	return (token);
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
