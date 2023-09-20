/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:49:58 by clovell           #+#    #+#             */
/*   Updated: 2023/09/16 02:55:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "lexer.h"

char	*get_token_desc(t_ttoken t, int tostring)
{
	char *const	des[] = {
		"NA", "E_TTNA",
		"Stdin Redirect", "E_TTLA",
		"Stdout Redirect", "E_TTRA",
		"Stdin Heredoc", "E_TTLLA",
		"Stdout Append Redirect", "E_TTRRA",
		"Double Quote", "E_TTDQ",
		"Single Quote", "E_TTSQ",
		"Word", "E_TTWD",
		"Pipe", "E_TTWD",
		"And", "E_TTNCA",
		"Or", "E_TTNCO",
	};

	return (des[get_token_index(t) * 2 + (tostring != 0)]);
}

size_t	get_token_index(t_ttoken t)
{
	int	i;

	i = 0;
	while ((t >> i) != 0)
		i++;
	return (i);
}

void	tlst_print(t_token *start)
{
	while (start != NULL)
	{
		printf("Token [%s]:%s\n", get_token_desc(start->type, 0), start->str);
		start = start->next;
	}
}
