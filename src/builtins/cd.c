/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:54:18 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/09/25 20:18:56 by mehdimirzai      ###   ########.fr       */
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
	{
		add_node_to_env(our_env, "PWD", getcwd(buff, PATH_MAX + 1));
		ref = *our_env;
	}
	while (ref2 && ft_strncmp(ref2->name, "OLDPWD", 6) != 0)
		ref2 = ref2->next;
	if (ref2 == NULL)
	{
		add_node_to_env(our_env, "OLDPWD", "NULL");
		ref2 = *our_env;
	}
	free(ref2->args);
	ref2->args = ref->args;
	ref->args = NULL;
	ref->args = ft_strdup(getcwd(buff, PATH_MAX + 1));
}

void	ft_cd(t_cmd *cmd, t_env **our_env)
{
	if (cmd->args == NULL)
		chdir(getenv("HOME"));
	else if (chdir(cmd->args->str) == -1)
	{
		write(2, "cd: no such file or directory: ", 31);
		ft_putstr_fd(cmd->args->str, 2);
		write(2, "\n", 1);
	}
	update_pwd(our_env);
}

// void	ft_cd(char *path, t_env **our_env)
// {
// 	if (path == NULL)
// 		chdir(getenv("HOME"));
// 	else if (chdir(path) == -1)
// 	{
// 		write(2, "cd: no such file or directory: ", 31);
// 		ft_putstr_fd(path, 2);
// 		write(2, "\n", 1);
// 	}
// 	update_pwd(our_env);
// }
