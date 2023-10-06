/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iolst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:47:11 by clovell           #+#    #+#             */
/*   Updated: 2023/10/06 16:24:57 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "iolst.h"
#include "error.h"

t_iolst	*iolst_add(t_ttoken tok, char *str, int dup, t_iolst **head)
{
	t_iolst	*next;
	t_iolst	*elem;

	next = *head;
	iolst_memman(&elem, false);
	ft_assert(elem == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
	elem->dup = dup != 0;
	elem->type = tok;
	elem->str = str;
	if (dup)
		elem->str = ft_strdup(str);
	ft_assert(elem->str == NULL, E_ERR_STRDUP, __FILE__, __LINE__);
	while (next != NULL && next->next != NULL)
		next = next->next;
	if (next != NULL)
		next->next = elem;
	if (head != NULL && *head == NULL)
		*head = elem;
	return (elem);
}

static void	iolst_destroy(t_iolst **lst)
{
	t_iolst	*curr;
	t_iolst	*next;

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

void	iolst_memman(t_iolst **lst, bool destroy)
{
	const t_iolst	builder = {0};

	if (!destroy)
	{
		*lst = malloc(sizeof(t_iolst));
		ft_assert(*lst == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		**lst = builder;
		return ;
	}
	iolst_destroy(lst);
}
