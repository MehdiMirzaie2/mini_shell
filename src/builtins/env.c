/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:02 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/12 23:59:41 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	valid_identifier(char **name_and_args, char *cmd)
{
	if (*name_and_args == NULL || ft_isdigit(*name_and_args[0])
		|| strrchr(name_and_args[0], '-') != NULL
		|| strrchr(name_and_args[0], '+') != NULL
		|| strrchr(name_and_args[0], '=') != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (false);
	}
	return (true);
}

int	unset(t_env **env, t_arglst *args)
{
	t_env *const	our_env = *env;
	t_env			*ref;
	t_env			*prev;
	t_env			*to_free;

	ref = our_env;
	prev = ref;
	if (args == NULL)
		return (0);
	if (!valid_identifier(&args->str, args->str))
		exit(256);
	while (ref && ft_strcmp(ref->name, args->str) != 0)
	{
		prev = ref;
		ref = ref->next;
	}
	if (ref == NULL)
		return (0);
	to_free = ref;
	if (prev == ref)
		*env = our_env->next;
	else
		prev->next = prev->next->next;
	free_env(to_free, false);
	return (0);
}

void	add_node_to_env(t_env **our_env, char *name, char *args)
{
	t_env	*ref;

	ref = malloc(sizeof(t_env));
	if (ref == NULL)
		return ;
	ref->name = ft_strdup(name);
	ref->args = ft_strdup(args);
	ref->next = *our_env;
	*our_env = ref;
}

// the following should append the path to existing paths
// export PATH=$PATH:/place/with/the/file
int	ft_export(t_env **our_env, t_arglst *args)
{
	t_env	*ref;
	char	**name_and_args;
	int		name_len;

	ref = *our_env;
	if (args == NULL)
		return (0);
	name_and_args = ft_split(args->str, '=');
	if (!valid_identifier(name_and_args, args->str))
		return (free_strarr(name_and_args) + 256);
	if (!ft_strchr(args->str, '='))
		return (free_strarr(name_and_args) + 0);
	name_len = ft_strlen(name_and_args[0]);
	while (ref && ft_strncmp(ref->name, name_and_args[0], name_len) != 0)
		ref = ref->next;
	if (ref != NULL)
	{
		free(ref->args);
		ref->args = ft_strdup(name_and_args[1]);
	}
	else
		add_node_to_env(our_env, name_and_args[0], name_and_args[1]);
	free_strarr(name_and_args);
	return (0);
}

void	ft_env(t_env *our_env)
{
	t_env	*ref;

	ref = our_env;
	while (ref->next != NULL)
	{
		if (!ft_strcmp(ref->name, "?"))
			ref = ref->next;
		else
		{
			printf("%s=%s\n", ref->name, ref->args);
			ref = ref->next;
		}
	}
	if (!ft_strcmp(ref->name, "?"))
		ref = ref->next;
	else
		printf("%s=%s\n", ref->name, ref->args);
}
