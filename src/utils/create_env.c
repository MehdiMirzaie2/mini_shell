/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:49:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/13 15:47:02 by clovell          ###   ########.fr       */
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

	ft_assert(key == NULL, E_ERR_NULLPARAM, __FILE__, __LINE__);
	next = our_env;
	while (next != NULL)
	{
		if (ft_strcmp(next->name, key) == 0)
		{
			free(next->args);
			next->args = value;
			return ;
		}
		next = next->next;
	}
	next = our_env;
	while (next->next != NULL)
		next = next->next;
	next->next = malloc(sizeof(t_env));
	next = next->next;
	next->name = ft_strdup(key);
	next->args = value;
	next->next = NULL;
}

char	**split_once(char *str, int limiter)
{
	char	**strings;
	int		limiter_pos;
	int		len;

	len = ft_strlen(str);
	limiter_pos = 0;
	while (str[limiter_pos] != limiter)
		limiter_pos++;
	strings = malloc(sizeof(char *) * 3);
	strings[0] = ft_substr(str, 0, limiter_pos);
	strings[1] = ft_substr(str, limiter_pos + 1, len);
	strings[2] = NULL;
	return (strings);
}

void	create_env(t_env *our_env, char **env)
{
	int		i;
	char	**name_and_args;
	char	**excess;

	i = 0;
	while (env[i] != NULL)
	{
		name_and_args = split_once(env[i], '=');
		our_env->name = name_and_args[0];
		our_env->args = name_and_args[1];
		excess = &name_and_args[2];
		our_env->next = NULL;
		if (env[i + 1] != NULL)
		{
			our_env->next = malloc(sizeof(t_env));
			our_env = our_env->next;
		}
		while (*excess)
			free(*(excess++));
		free(name_and_args);
		i++;
	}
}

void	free_env(t_env *env, bool all)
{
	t_env	*next;

	if (all)
	{
		next = env;
		while (next)
		{
			env = next;
			next = next->next;
			free(env->name);
			free(env->args);
			free(env);
		}
	}
	else
	{
		free(env->name);
		free(env->args);
		free(env);
	}
}
