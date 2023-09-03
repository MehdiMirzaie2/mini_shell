/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:49:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/03 22:36:31 by clovell          ###   ########.fr       */
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
	return (NULL);
}

void	env_set(t_env *our_env, char *key, char *value)
{
	t_env	*next;

	if (key == NULL)
		ft_errx(E_BADPARAM, E_MSG_NULL_PARAM, __FILE__, __LINE__);
	next = our_env;
	while (next != NULL)
	{
		if (ft_strcmp(next->name, key) == 0)
		{
			free(next->args);
			next->args = ft_strdup(value);
			return ;
		}
		next = next->next;
	}
	next = our_env;
	while (next->next != NULL)
		next = next->next;
	next->next = malloc(sizeof(t_env));
	next = next->next;
	next->name = key;
	next->args = ft_strdup(value);
	next->next = NULL;
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
