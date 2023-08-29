/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:49:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/29 14:42:11 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*env_get(t_env *our_env, char *name)
{
	while (our_env != NULL)
	{
		if (ft_strcmp(our_env->name, name) == 0)
			return (our_env->args);
		our_env = our_env->next;
	}
	return ("does not Exist");
}

void    create_env(t_env *our_env, char **env)
{
	int		i;
	char	**name_and_args;
	t_env	*ref;

	ref = our_env;
	i = 0;
	while (env[i] != NULL)
	{
		name_and_args = ft_split(env[i], '=');
		our_env->name = name_and_args[0];
		our_env->args = name_and_args[1];
		our_env->next = NULL;
		if (env[i + 1] != NULL)
		{
			our_env->next = malloc(sizeof(t_env));
			our_env = our_env->next;
		}
		++i;
	}
	our_env = ref;
}
