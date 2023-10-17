/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:00 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/17 12:10:00 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

void	export_null(t_env *ref, int *e_status)
{
	while (ref != NULL)
	{
		printf("declare -x %s=\"%s\"\n", ref->name, ref->args);
		ref = ref->next;
	}
	*e_status = 0;
}

bool	move_next(char **name_and_args, t_arglst **args, int *e_status)
{
	if (!valid_identifier(name_and_args, (*args)->str))
	{
		*e_status = free_strarr(name_and_args) + 256;
		*args = (*args)->next;
		return (true);
	}
	if (!ft_strchr((*args)->str, '='))
	{
		*e_status = free_strarr(name_and_args);
		*args = (*args)->next;
		return (true);
	}
	return (false);
}

void	ft_export(t_env **our_env, t_arglst *args, int *e_status)
{
	t_env	*ref;
	char	**name_and_args;

	ref = *our_env;
	if (args == NULL)
		return (export_null(ref, e_status));
	while (args)
	{
		name_and_args = ft_split(args->str, '=');
		if (move_next(name_and_args, &args, e_status))
			continue ;
		while (ref && ft_strncmp(ref->name, name_and_args[0],
				ft_strlen(name_and_args[0])) != 0)
			ref = ref->next;
		if (ref != NULL)
		{
			free(ref->args);
			ref->args = ft_strdup(name_and_args[1]);
		}
		else
			add_node_to_env(our_env, name_and_args[0], name_and_args[1]);
		free_strarr(name_and_args);
		args = args->next;
	}
}
