#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "util.h"
#include "error.h"


t_strlst *strlst_add(char *str, int dup, t_strlst **head)
{
	t_strlst	*next;
	t_strlst	*elem;

	next = *head;
	strlst_memman(&elem, false);
	if (elem == NULL)
		ft_errx(E_MALLOCFAIL, E_MSG_STRLST_MALLOC, __FILE__, __LINE__);
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

void strlst_memman(t_strlst **lst, bool destroy)
{
	const t_strlst builder = {0};
	t_strlst	*curr;
	t_strlst	*next;

	if (!destroy)
	{
		*lst = malloc(sizeof(t_strlst));
		if (*lst == NULL)
			ft_errx(E_MALLOCFAIL, E_MSG_STRLST_MALLOC, __FILE__, __LINE__);
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
