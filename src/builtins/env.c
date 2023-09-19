/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:02 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/19 14:17:51 by mehdimirzai      ###   ########.fr       */
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
	while (ft_strcmp(ref->name, name) != 0)
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

void add_node_to_env(t_env **our_env, char *name, char *args)
{
    t_env *ref = malloc(sizeof(t_env));
    if (ref == NULL) {
        // Handle memory allocation failure
        return;
    }

    ref->name = ft_strdup(name);
    ref->args = ft_strdup(args);
    ref->next = *our_env;
    *our_env = ref;
}


// the following should append the path to existing paths
// export PATH=$PATH:/place/with/the/file

bool	valid_identifier(char **name_and_args, char *args)
{
	if (*name_and_args == NULL || ft_isdigit(*name_and_args[0])
		|| strrchr(name_and_args[0], '-') != NULL
		|| strrchr(name_and_args[0], '+') != NULL)
	{
		ft_putstr_fd("export: \'", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (false);
	}
	return (true);
}

void	export(t_env **our_env, char *args)
{
	t_env	*ref;
	char **name_and_args;
	int name_len;

	ref = *our_env;
	name_and_args = ft_split(args, '=');
	if (!valid_identifier(name_and_args, args))
		return ;
	name_len = ft_strlen(name_and_args[0]);
	// if (ft_isdigit(*name_and_args[0]))
	// {
	// 	ft_putstr_fd("export: not an identifier: ", 2);
	// 	ft_putstr_fd(name_and_args[0], 2);
	// 	return ;
	// }
	while (ref && ft_strncmp(ref->name, name_and_args[0], name_len) != 0)
		ref = ref->next;
	if (ref != NULL)
	{
		free(ref->args);
		ref->args = ft_strdup(name_and_args[1]);
	}
	else
		add_node_to_env(our_env, name_and_args[0], name_and_args[1]);
	free(name_and_args[0]);
	free(name_and_args[1]);
}

void	ft_env(t_env *our_env)
{
	t_env	*ref;

	ref = our_env;
	while (ref->next != NULL)
	{
		printf("%s=%s\n", ref->name, ref->args);
		ref = ref->next;
	}
	printf("%s=%s\n", ref->name, ref->args);
}
