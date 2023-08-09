/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:07:23 by clovell           #+#    #+#             */
/*   Updated: 2023/08/09 20:18:42 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum	e_tokentype
{
	E_NA,
	E_ERR,
	E_LEX,
	E_DQ,
	E_SQ,
	E_AL,
	E_AR,
	E_ALL,
	E_ARR,
}:

/* Token represents a specific symbol or a word 
 * Shallow: A shallow token has 'str' as a non-copied/non-filtered string.
 * Deep:	A deep token has 'str' as a copied/filtered string.
 */
struct s_token
{
	char *str;
   	char c;
	char n;
	
	t_token *next;
}

t_tokentype get_token(char c, char n, char **adv)
{
	t_toktype type;

	(*adv)++;
	type = E_NA;
	if (isspace(c))
		return (type);
	type |= (c == '\"' * E_DQ);
	type |= (c == '\'' * E_SQ);
	type |= (c == '<' * E_AR);
	type |= (c == '<' * E_AL);
	type |= ((c == '<' && n == '<') * E_ALL);
	type |= ((c == '>' && n == '>') * E_ARR);
	if (type == E_ALL || type == E_ARR)
		(*adv)++;
	if (type == E_NA)
		return (E_LEX);
	return (type);
}


t_token *new_token()
{
	t_token *token;

	token = calloc(1, sizeof(t_token));
	token->str = NULL;
	token->c = '\0';
	token->n = '\0';
	return (token);
}

t_token *token_shallow(char *line)
{
	t_token	*token;
	t_token *latest;

	token = new_token();
	latest = token;
	while (*line)
	{
		token->str = line;
		token->c = line[0];
		token->n = line[1];
		token->type = get_token(line[0], line[1], line);
		if (token->type == E_NA)
			continue;
		token_deep(latest);
		latest->next = new_token();
		latest = latest->next;
	}
}

static char *strcpyc(char *line, char c)
{
	int len;
	char *str;

	len = 0;
	while (line[len] != c && line[len])
		len++;
	str = calloc(sizeof(char), len + 1);
	strlcpy(str, line, len);
	return (str);
}

/* converts a shallow token to a deep token */
void token_deep(t_token *token)
{
	t_token *insert;

	if (token->type == E_SQ || token->type == E_DQ)
	{
		insert = new_token();
		insert->type = E_STR;
		insert->str = strcpyc(token->str, token->c);
		insert->next = token->next;
		token->next = insert;
	}
}

int find_token_pair(char *line, char t)
{
	int depth;

	while (*line && get_token() == 
}
