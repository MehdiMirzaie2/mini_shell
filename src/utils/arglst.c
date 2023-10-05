/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:35:59 by clovell           #+#    #+#             */
/*   Updated: 2023/10/05 14:07:05 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "arglst.h"
#include "error.h"

t_arglst	*arglst_add(char *str, int dup, t_arglst **head)
{
	t_arglst	*next;
	t_arglst	*elem;

	next = *head;
	arglst_memman(&elem, false);
	ft_assert(elem == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
	elem->dup = dup != 0;
	elem->str = str;
	if (dup)
		elem->str = ft_strdup(str);
	ft_assert(elem->str == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
	while (next != NULL && next->next != NULL)
		next = next->next;
	if (next != NULL)
		next->next = elem;
	if (head != NULL && *head == NULL)
		*head = elem;
	return (elem);
}

void	arglst_memman(t_arglst **lst, bool destroy)
{
	const t_arglst	builder = {0};
	t_arglst		*curr;
	t_arglst		*next;

	if (!destroy)
	{
		*lst = malloc(sizeof(t_arglst));
		ft_assert(*lst == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		**lst = builder;
		return ;
	}
	if (*lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->dup != 0)
			free(curr->str);
		curr->str = NULL;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
