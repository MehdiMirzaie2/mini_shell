/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:49:13 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/24 14:30:05 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// int setenv (const char *name, const char *value, int replace)
// {
// 	if (name == NULL || *name == '\0' || strchr (name, '=') != NULL)
// 	{
// 		__set_errno (EINVAL);
// 		return -1;
// 	}
// 	return __add_to_environ (name, value, NULL, replace);
// }
// int unsetenv (const char *name)
// {
// 	size_t len;
// 	char **ep;

// 	if (name == NULL || *name == '\0' || strchr (name, '=') != NULL)
// 	{
// 		__set_errno (EINVAL);
// 		return -1;
// 	}
// 	len = strlen (name);
// 	LOCK;
// 	ep = __environ;
// 	if (ep != NULL)
// 	while (*ep != NULL)
// 		{
// 			if (!strncmp (*ep, name, len) && (*ep)[len] == '=')
// 				{
// 					/* Found it.  Remove this pointer by moving later ones back.  */
// 					char **dp = ep;
// 					do
// 					dp[0] = dp[1];
// 					while (*dp++);
// 					/* Continue the loop in case NAME appears again.  */
// 				}
// 			else
// 				++ep;
// 		}
// 	UNLOCK;
// 	return 0;
// }

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

void    create_env(t_env *our_env, char **env)
{
	int		i;
	int		index;
	int		len;
	t_env	*ref;

	ref = our_env;
	i = 0;
	while (env[i] != NULL)
	{
		index = 0;
		while (env[i][index] != '=')
			index++;
		len = strlen(*env);
		our_env->next = NULL;
		our_env->name = ft_substr(env[i], 0, index);
		our_env->args = ft_substr(env[i], index + 1, len);
		if (env[i + 1] != NULL)
		{
			our_env->next = malloc(sizeof(t_env));
			our_env = our_env->next;
		}
		++i;
	}
	our_env = ref;
}

//
