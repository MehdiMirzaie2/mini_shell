/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:33:30 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/10 11:29:47 by mehdimirzai      ###   ########.fr       */
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

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*next;
	int		size;

	next = env;
	size = 0;
	while (next != NULL)
	{
		next = next->next;
		size++;
	}
	array = malloc(sizeof(char *) * (size + 1));
	next = env;
	array[size] = NULL;
	while (--size >= 0)
	{
		array[size] = ft_strfmt("%s=%s", next->name, next->args);
		next = next->next;
	}
	return (array);
}

int	is_directory_exists(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

void	error_execve(char *cmd, char *path)
{
	if (is_directory_exists(cmd))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else
		ft_putstr_fd(ft_strfmt("%s: %s\n", path,
				strerror(errno)), 2);
}

void	execute_system_cmds(t_cmd *cmd, t_env *env)
{
	char		**cmd_args_joined;
	char		*cmd_plus_path;
	char		**paths_splitted;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, handle_sigintexecute);
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
	if (execve(cmd_plus_path, cmd_args_joined, env_to_array(env)) < 0)
	{
		error_execve(cmd->cmd, cmd_args_joined[0]);
		exit(126);
	}
}
