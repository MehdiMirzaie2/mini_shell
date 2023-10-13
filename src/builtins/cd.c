/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:54:18 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/13 16:16:16 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
goes through the env, locates PWD or OLD_PWD, then changes them accordingly.
*/
void	update_pwd(t_env **our_env)
{
	t_env	*ref;
	t_env	*ref2;
	char	buff[PATH_MAX + 1];

	ref = *our_env;
	ref2 = *our_env;
	while (ref && ft_strncmp(ref->name, "PWD", 3) != 0)
		ref = ref->next;
	if (ref == NULL)
		add_node_to_env(our_env, "PWD", getcwd(buff, PATH_MAX + 1));
	if (ref == NULL)
		ref = *our_env;
	while (ref2 && ft_strncmp(ref2->name, "OLDPWD", 6) != 0)
		ref2 = ref2->next;
	if (ref2 == NULL)
		add_node_to_env(our_env, "OLDPWD", "NULL");
	if (ref2 == NULL)
		ref2 = *our_env;
	free(ref2->args);
	ref2->args = ref->args;
	ref->args = NULL;
	if (getcwd(buff, PATH_MAX + 1))
		ref->args = ft_strdup(buff);
	else
		ref->args = ft_strdup("");
}

int	ft_cd(t_cmd *cmd, t_env **our_env)
{
	char	*destination;

	if (cmd->args == NULL || !ft_strncmp(cmd->args->str, "~", 2))
		chdir(getenv("HOME"));
	else if (!ft_strncmp(cmd->args->str, "-", 2))
	{
		destination = env_get(*our_env, "OLDPWD");
		if (!destination)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			return (256);
		}
		chdir(destination);
	}
	else if (chdir(cmd->args->str) == -1)
	{
		ft_printf_fd(2, "cd: %s: No such file or directory\n", cmd->args->str);
		return (256);
	}
	update_pwd(our_env);
	return (0);
}
