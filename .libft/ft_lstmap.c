/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:31:42 by clovell           #+#    #+#             */
/*   Updated: 2023/03/15 17:18:55 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

/* Duplicates a lists, where the content is transformed by the fucntion f 
 *
 * Implementation Notes:
 * t_list **new, stores a reference to where ft_lstnew should output to.
 * For the first loop that'll be the t_list *start variable, for any other
 * it will be start(->next->next..nth) (loop nth times) 
 * see 'new = &(*new)->next;'
 * */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**new;
	t_list	*start;
	void	*content;

	start = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		if (!start)
			new = &start;
		else
			new = &(*new)->next;
		*new = ft_lstnew(content);
		if (!(*new) || !content)
		{
			del(content);
			ft_lstclear(&start, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (start);
}
