/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:23:53 by clovell           #+#    #+#             */
/*   Updated: 2023/08/30 14:29:37 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"
#include "libft.h"

/* Advanced a token list.
 * Advances token list `adv` by `amount` amount and ...
 * Stores the token type in `type`.
 *
 * RETURN VALUES.
 * returns -1 if adv or it's content was NULL,
 * returns -2 if it couldn't advanced `amount` amount.
 * For value > 0 it means it had `value` advances left to target.
 * Meaning if value != 0 it couldn't fully advance (list not long enough).
 */
int token_adv(t_token **adv, t_ttoken *type, int amount)
{
	t_token *start;
	
	if (adv == NULL || *adv == NULL)
		return (-1);
	start = *adv;
	while (start->next && amount > 0)
	{
		start = start->next;
		amount--;
	}
	if (amount != 0)
		return (amount);
	*adv = start;
	*type = start->type;
	return (0);
}

char	*get_token_desc(t_ttoken t, int tostring)
{
	char *const	des[] = 
	{
		"NA", "E_NA",
		"Double Quote", "E_DQ",
		"Single Quote", "E_SQ",
		"Stdin Redirect", "E_LA",
		"Stdout Redirect", "E_RA",
		"Stdin Wait Redirect", "E_LLA",
		"Stdout Append Redirect", "E_RRA",
		"Word", "E_WD",
		"Pipe", "E_WD",
		"Start of Cmd", "E_ALL"
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

int	isttoken(char c)
{
	return (ft_strchr("\'\"|<>", c) != NULL);
}

