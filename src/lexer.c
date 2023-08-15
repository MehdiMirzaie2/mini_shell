#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft_extra.h"
#include "libft.h"
#include "lexer.h"

char *get_token_desc(t_ttoken t)
{
	if (t == E_GS)
		return "Grouped Sequence";
	if (t == E_DQ)
		return "Double Quote";
	else if (t == E_SQ)
		return "Single Quote";
	else if (t == E_LA)
		return "Stdin Redirect";
	else if (t == E_RA)
		return "Stdout Redirect";
	else if (t == E_WD)
		return "Word";
	else if (t == E_P)
		return "Pipe";
	else if (t == E_ALL)
		return "Start of Cmd";
	return "unknown";
}

t_token *tlst_token_new(char *str, t_ttoken type, t_token *parent)
{
	t_token *token;
	
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

t_token *tlst_create(char *str)
{
	t_token *start;
	t_token *last;
	char c;

	start = tlst_token_new(str, E_ALL, NULL);
	last = start;
	while (*str)
	{
		while (isspace(*str))
				str++;
		c = *str;
		if (*str == '\'')
			last = tlst_token_new(str++, E_SQ, last);	
		else if (*str == '\"')
			last = tlst_token_new(str++, E_DQ, last);
		else if (*str == '<')
			last = tlst_token_new(str, E_LA, last);
		else if (*str == '>')
			last = tlst_token_new(str, E_RA, last);
		else if (*str == '|')
			last = tlst_token_new(str, E_P, last);
		else if (isascii(*str))
		{
			last = tlst_token_new(str, E_WD, last);
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
	/*return (start);*/
	return (tlst_dup_pass(start));
}

int ft_isspace(int c)
{
	// DO NOT USE THIS IMPLEMENTATION, PLEASE REIMPLEMENT
	return (isspace(c));
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
		if ((next->type & (E_GS | E_WD)) != 0)
			next->str = ft_strdupi(next->str, tlst_token_dup);
		else
			next->str = ft_strdup(lstr);
		if (next->str == NULL)
			return (tlst_destroy(head));
		else if (next->type != E_ALL)
			next->dup = true;
		next = next->next;
	}
	return (head);
}


void tlst_print(t_token *start)
{
	while (start != NULL)
	{
		printf("Token [%s]:%s\n", get_token_desc(start->type), start->str);
		start = start->next;
	}
}

// REMOVE BEFORE EVAL
const char* __asan_default_options() { return "detect_leaks=0";}
