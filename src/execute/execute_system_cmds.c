/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:33:30 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/13 18:14:14 by clovell          ###   ########.fr       */
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

void	error_execve(char *cmd)
{
	if (is_directory_exists(cmd))
	{
		ft_printf_fd(2, "%s: is a directory\n", cmd);
		exit(126);
	}
	else if (cmd[0] == '.')
		return ;
	else
	{
		ft_printf_fd(2, "%s: %s\n", cmd, strerror(errno));
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
}

static void	execute_sys_cmd(t_cmd *cmd, char *cmd_path, char **argv, t_env *env)
{
	char	**envp;

	envp = env_to_array(env);
	if (execve(cmd_path, argv, envp) < 0)
	{
		free_strarr(envp);
		error_execve(cmd->cmd);
		free_strarr(argv);
		exit(126);
	}
}

void	execute_system_cmds(t_cmd *cmd, t_env *env)
{
	char		**cmd_args_joined;
	char		*cmd_plus_path;
	char		**paths_splitted;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, handle_sigintexecute);
	if (ft_strchr(cmd->cmd, '/'))
	{
		cmd_plus_path = cmd->cmd;
		if (cmd->cmd[0] == '.')
			cmd->cmd = ft_substr(cmd->cmd, 2, ft_strlen(cmd->cmd));
		else
		{
			error_execve(cmd->cmd);
			cmd->cmd = ft_substr(cmd->cmd, ft_strchr(cmd->cmd, '/') + 1
				   	- cmd->cmd, ft_strlen(cmd->cmd));
		}
		cmd_args_joined = join_cmd(cmd);
	}
	else if (env_get(env, "PATH"))
	{
		paths_splitted = ft_split(env_get(env, "PATH"), ':');
		cmd_plus_path = cmd_path(paths_splitted, cmd->cmd);
	}
	else
		cmd_plus_path = cmd->cmd;
	cmd_args_joined = join_cmd(cmd);
	execute_sys_cmd(cmd, cmd_plus_path, cmd_args_joined, env);
}
