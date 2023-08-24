/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:02 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/23 16:29:56 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
// use the function cris made.

void	unset(t_env *our_env, char *name)
{
	t_env	*ref;
	t_env	*prev;
	t_env	*to_free;

	ref = our_env;
	while (!ft_strcmp(ref->name, name))
	{
		prev = ref;
		ref = ref->next;
	}
	to_free = ref;
	prev->next = prev->next->next;
	free(to_free->args);
	free(to_free->name);
	free(to_free);
}

void	add_node(t_env *our_env, char *name, char *args)
{
	t_env	*ref;

	ref = malloc(sizeof(t_env));
	ref->name = ft_strdup(name);
	ref->args = ft_strdup(args);
	ref->next = our_env;
	our_env = ref;
	ref = NULL;
}

// the following should append the path to existing paths
// export PATH=$PATH:/place/with/the/file

void	export(t_env *our_env, char *name, char *args)
{
	t_env	*ref;

	ref = our_env;
	if (ft_isdigit(*name))
	{
		ft_putstr("export: not an identifier: ");
		ft_putstr(name);
		return ;
	}
	add_node(our_env, name, args);
}

void	ft_env(t_env *our_env)
{
	t_env	*ref;

	ref = our_env;
	while (ref->next != NULL)
	{
		ft_putstr_fd(ref->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(ref->args, 1);
		ref = ref->next;
	}
	ft_putstr_fd(ref->name, 1);
	ft_putchar_fd('=', 1);
	ft_putstr_fd(ref->args, 1);
}
