/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:33:30 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/09/25 18:13:31 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execute.h"

char	*get_lastredirect(t_iolst	*redirects)
{
	t_iolst	*ref_redirects;

	ref_redirects = redirects;
	if (redirects == NULL)
		return (NULL);
	while (ref_redirects->next)
		ref_redirects = ref_redirects->next;
	return (ref_redirects->str);
}

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
	joined[num_args] = NULL;
	num_args = 1;
	args_ref = cmd->args;
	while (args_ref && num_args >= 1)
	{
		joined[num_args++] = args_ref->str;
		args_ref = args_ref->next;
	}
	return (joined);
}

/*same as strcat but it places a '/' between the joined strings*/
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

	if (strncmp(cmd, "./", 2) == 0)
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
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" :command not found\n", 2);
	exit(127);
}

void	execute_system_cmds(t_cmd *cmd, t_env *env)
{
	char		**cmd_args_joined;
	char		*cmd_plus_path;
	char		**paths_splitted;
	extern char	**environ;

	cmd_args_joined = join_cmd(cmd);
	if (ft_strchr(cmd->cmd, '/'))
	{
		cmd_plus_path = cmd->cmd;
		cmd->cmd = ft_substr(cmd->cmd, ((ft_strrchr(cmd->cmd, '/') + 1)
					- cmd->cmd), ft_strlen(cmd->cmd));
		cmd_args_joined = join_cmd(cmd);
	}
	else
	{
		paths_splitted = ft_split(env_get(env, "PATH"), ':');
		cmd_plus_path = cmd_path(paths_splitted, cmd->cmd);
	}
	if (execve(cmd_plus_path, cmd_args_joined, environ) < 0)
	{
		ft_putstr_fd("failed at execve\n", 2);
		exit(EXIT_FAILURE);
	}
}
