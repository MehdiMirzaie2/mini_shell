/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_arg_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:56:37 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/13 14:08:21 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

char	**join_cmd(t_cmd *cmd)
{
	char		**joined;
	int			num_args;
	t_arglst	*args_ref;

	num_args = get_num_args(cmd);
	joined = malloc(sizeof(char *) * (num_args + 2));
	joined[0] = cmd->cmd;
	if (num_args == 0)
		return (joined[1] = NULL, joined);
	joined[num_args + 1] = NULL;
	num_args = 1;
	args_ref = cmd->args;
	while (args_ref && num_args >= 1)
	{
		joined[num_args++] = args_ref->str;
		args_ref = args_ref->next;
	}
	return (joined);
}

char	*ft_cmdcat(char *path, char *cmd)
{
	int		len_path;
	int		len_cmd;
	char	*file_path;
	int		i;
	int		j;

	i = -1;
	j = -1;
	len_path = ft_strlen(path);
	len_cmd = ft_strlen(cmd);
	file_path = malloc(sizeof(char) * (len_cmd + len_path + 2));
	if (file_path == NULL)
		return (NULL);
	while (++i < len_path)
		file_path[i] = path[i];
	file_path[i++] = '/';
	while (++j < len_cmd)
		file_path[i + j] = cmd[j];
	file_path[i + j] = '\0';
	return (file_path);
}

char	*cmd_path(char **splitted_paths, char *cmd)
{
	char	*file_path;
	int		val;

	if (ft_strncmp(cmd, "./", 2) == 0)
		return (cmd);
	while (*splitted_paths)
	{
		file_path = ft_cmdcat(*splitted_paths, cmd);
		val = access(file_path, X_OK);
		if (val == 0)
			return (file_path);
		free(file_path);
		++splitted_paths;
	}
	ft_printf_fd(2, "%s: command not found\n", cmd);
	exit(127);
}
