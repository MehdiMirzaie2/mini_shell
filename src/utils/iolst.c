/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iolst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:47:11 by clovell           #+#    #+#             */
/*   Updated: 2023/08/30 12:50:32 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "iolst.h"
#include "error.h"


t_iolst *iolst_add(char *redir, char *str, int dup, t_iolst **head)
{
	t_iolst	*next;
	t_iolst	*elem;

	next = *head;
	iolst_memman(&elem, false);
	if (elem == NULL)
		ft_errx(E_MALLOCFAIL, E_MSG_IOLST_MALLOC, __FILE__, __LINE__);
	elem->dup = dup != 0;
	elem->redir = redir;
	elem->str = str;
	if (dup)
		elem->str = ft_strdup(str);
	if (dup)
		elem->redir = ft_strdup(redir);
	if (elem->str == NULL)
		ft_errx(E_MALLOCFAIL, E_MSG_STRDUP_MALLOC, __FILE__, __LINE__);
	if (elem->redir == NULL)
		ft_errx(E_MALLOCFAIL, E_MSG_STRDUP_MALLOC, __FILE__, __LINE__);
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
		if (curr->dup != 0)
			free(curr->redir);
		curr->str = NULL;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void iolst_memman(t_iolst **lst, bool destroy)
{
	const t_iolst builder = {0};

	if (!destroy)
	{
		*lst = malloc(sizeof(t_iolst));
		if (*lst == NULL)
			ft_errx(E_MALLOCFAIL, E_MSG_IOLST_MALLOC, __FILE__, __LINE__);
		**lst = builder;
		return ;
	}
	iolst_destroy(lst);
}
