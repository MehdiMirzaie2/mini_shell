/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:37:42 by clovell           #+#    #+#             */
/*   Updated: 2023/10/13 16:43:29 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*next;
	int		size;

	next = env;
	size = 0;
	while (next != NULL)
	{
		next = next->next;
		size++;
	}
	array = malloc(sizeof(char *) * (size + 1));
	next = env;
	array[size] = NULL;
	while (--size >= 0)
	{
		array[size] = ft_strfmt("%s=%s", next->name, next->args);
		next = next->next;
	}
	return (array);
}
