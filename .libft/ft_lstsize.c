/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:33:25 by clovell           #+#    #+#             */
/*   Updated: 2023/03/14 16:39:42 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*next;

	if (lst == NULL)
		return (0);
	next = lst;
	count = 0;
	while (next != NULL)
	{
		next = next->next;
		count++;
	}
	return (count);
}
