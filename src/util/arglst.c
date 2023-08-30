#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "arglst.h"
#include "error.h"


t_arglst *arglst_add(char *str, int dup, t_arglst **head)
{
	t_arglst	*next;
	t_arglst	*elem;

	next = *head;
	arglst_memman(&elem, false);
	if (elem == NULL)
		ft_errx(E_MALLOCFAIL, E_MSG_ARGLST_MALLOC, __FILE__, __LINE__);
	elem->dup = dup != 0;
	elem->str = str;
	if (dup)
		elem->str = ft_strdup(str);
	if (elem->str == NULL)
		ft_errx(E_MALLOCFAIL, E_MSG_STRDUP_MALLOC, __FILE__, __LINE__);
	while (next != NULL && next->next != NULL)
		next = next->next;
	if (next != NULL)
		next->next = elem;
	if (head != NULL && *head == NULL)
		*head = elem;
	return (elem);
}

void arglst_memman(t_arglst **lst, bool destroy)
{
	const t_arglst builder = {0};
	t_arglst	*curr;
	t_arglst	*next;

	if (!destroy)
	{
		*lst = malloc(sizeof(t_arglst));
		if (*lst == NULL)
			ft_errx(E_MALLOCFAIL, E_MSG_ARGLST_MALLOC, __FILE__, __LINE__);
		**lst = builder;
		return ;
	}
	if (*lst == NULL)
		return;
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
