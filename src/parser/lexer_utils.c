/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:21:50 by clovell           #+#    #+#             */
/*   Updated: 2023/08/30 14:29:12 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "lexer.h"

void tlst_print(t_token *start)
{
	while (start != NULL)
	{
		printf("Token [%s]:%s\n", get_token_desc(start->type, 0), start->str);
		start = start->next;
	}
}
