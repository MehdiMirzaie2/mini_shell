/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:33:30 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/14 14:59:06 by mehdimirzai      ###   ########.fr       */
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
	// printf("\ncmd = %s\n", cmd);
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

struct s_exec_info
{
	char *abs_cmd;
	char **argv;
};

struct s_exec_info	get_executable(t_cmd *cmd, char **paths)
{
	struct s_exec_info	exec;

	if (ft_strchr(cmd->cmd, '/'))
	{
		exec.abs_cmd = cmd->cmd;
		if (cmd->cmd[0] == '.')
			cmd->cmd = ft_substr(cmd->cmd, 2, ft_strlen(cmd->cmd));
		else
		{
			error_execve(cmd->cmd);
			cmd->cmd = ft_substr(cmd->cmd, ft_strchr(cmd->cmd, '/') + 1
				   	- cmd->cmd, ft_strlen(cmd->cmd));
		}
	}
	else if (paths)
		exec.abs_cmd = cmd_path(paths, cmd->cmd);
	else
		exec.abs_cmd = cmd->cmd;
	exec.argv = join_cmd(cmd);
	return (exec);
}

void	execute_system_cmds(t_cmd *cmd, t_env *env)
{
	struct s_exec_info	exec;
	char				**paths;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, handle_sigintexecute);
	paths = NULL;
	if (env_get(env, "PATH"))
		paths = ft_split(env_get(env, "PATH"), ':');
	exec = get_executable(cmd, paths);
	execute_sys_cmd(cmd, exec.abs_cmd, exec.argv, env);
}
