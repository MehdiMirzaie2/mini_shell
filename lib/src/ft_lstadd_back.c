/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:35:51 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/03/16 14:14:52 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (!new)
		return ;
	if (lst)
	{
		end = ft_lstlast(*lst);
		if (end)
			end->next = new;
		else
			*lst = new;
	}
}

// #include <stdlib.h>
// #include <stdio.h>

// int main(void)
// {
//     t_list *lst = NULL;
//     t_list *new_node;

//     // Create the first node
//     new_node = malloc(sizeof(t_list));
//     new_node->content = "First node";
//     new_node->next = NULL;
//     lst = new_node;

//     // Add more nodes to the back of the list
//     new_node = malloc(sizeof(t_list));
//     new_node->content = "Second node";
//     new_node->next = NULL;
//     ft_lstadd_back(&lst, new_node);

//     new_node = malloc(sizeof(t_list));
//     new_node->content = "Third node";
//     new_node->next = NULL;
//     ft_lstadd_back(&lst, new_node);

//     // Print the content of the list
//     t_list *curr_node = lst;
//     while (curr_node != NULL)
//     {
//         printf("%s\n", (char*)curr_node->content);
//         curr_node = curr_node->next;
//     }

//     return 0;
// }