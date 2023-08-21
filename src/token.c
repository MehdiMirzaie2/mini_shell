/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:23:53 by clovell           #+#    #+#             */
/*   Updated: 2023/08/17 13:29:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
