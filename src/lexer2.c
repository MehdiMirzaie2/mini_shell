#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

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

t_token *create_token(char *str, t_ttoken type, t_token *parent)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	token->str = str;
	token->type = type;
	token->next = NULL;
	while (parent != NULL && parent->next != NULL)
		parent = parent->next;
	if (parent != NULL)
		parent->next = token;
	return (token);	
}

t_token *tokenise(char *str)
{
	t_token *start;
	t_token *last;
	char c;

	start = create_token(str, E_ALL, NULL);
	last = start;
	while (*str)
	{
		while (isspace(*str))
				str++;
		c = *str;
		if (*str == '\'')
			last = create_token(str++, E_SQ, last);	
		else if (*str == '\"')
			last = create_token(str++, E_DQ, last);
		else if (*str == '<')
			last = create_token(str, E_LA, last);
		else if (*str == '>')
			last = create_token(str, E_RA, last);
		else if (*str == '|')
			last = create_token(str, E_P, last);
		else if (isascii(*str))
		{
			last = create_token(str, E_WD, last);
			while (*str && !isspace(*str))
				str++;
		}
		while (*str && (c == '\'' || c == '\"') && *str != c)
			str++;
		if (*str == c)
			str++;
	}
	return (start);
}

int ft_isspace(int c)
{
	// DO NOT USE THIS IMPLEMENTATION, PLEASE REIMPLEMENT
	return (isspace(c));
}

/*void	token_dup_pass(t_token *head)*/
/*{*/
/*    t_token *next;*/
/*    char lstr[2];*/
	
/*    lstr[1] = '\0';*/
/*    next = head;*/
/*    while (next != NULL)*/
/*    {*/
/*        lstr[0] = next->str[0];*/
/*        if ((next->type & E_GS != 0))*/
/*            next->str = ft_strdupu(&next->str[1], lstr);*/
/*        //else if (next->type == E_WD)*/
/*        //	next->str = ft_strdupct(next->str, ft_isspace);*/
/*        else*/
/*            next->str = ft_strdup(lstr);*/
/*    //	else if (next->type == )*/
/*        next = next->next;*/
/*    }*/

/*}*/


void print_tokenlst(t_token *start)
{
	while (start != NULL)
	{
		printf("Token [%s]:%s\n", get_token_desc(start->type), start->str);
		start = start->next;
	}
}

// REMOVE BEFORE EVAL
const char* __asan_default_options() { return "detect_leaks=0";}
