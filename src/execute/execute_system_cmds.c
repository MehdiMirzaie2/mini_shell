/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_system_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:33:30 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/09/16 10:25:45 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**join_cmd(t_cmd *cmd)
{
	char		**joined;
	int			num_args;
	t_arglst	*args_ref;

	num_args = 1;
	args_ref = cmd->args;
	while (args_ref)
	{
		args_ref = args_ref->next;
		num_args++;
	}
	joined = malloc(sizeof(char *) * num_args + 1);
	joined[0] = cmd->cmd;
	num_args = 1;
	args_ref = cmd->args;
	while (args_ref)
	{
		joined[num_args++] = args_ref->str;
		args_ref = args_ref->next;
	}
	joined[num_args] = NULL;
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
	perror(" command not found");
	exit(127);
}

void	execute_system_cmds(t_cmd *cmd, t_env *env)
{
	char	**cmd_args_joined;
	char	*cmd_plus_path;
	char	**paths_splitted;
	extern char** environ;

	cmd_args_joined = join_cmd(cmd);
	if (ft_strchr(cmd->cmd, '/'))
	{
		cmd_plus_path = cmd->cmd;
		cmd->cmd = ft_substr(cmd->cmd, ((ft_strrchr(cmd->cmd, '/') + 1) - cmd->cmd), ft_strlen(cmd->cmd));
		cmd_args_joined = join_cmd(cmd);
	}
	else
	{
		paths_splitted = ft_split(env_get(env, "PATH"), ':');
		cmd_plus_path = cmd_path(paths_splitted, cmd->cmd);
	}
	// FILE *fd = fopen("outfile", "w");
	// fprintf(fd, "%s\t%s\n", cmd_plus_path, cmd_args_joined[1]);
	// dup2(STDERR_FILENO, STDOUT_FILENO);
	// close(STDERR_FILENO);
	if (execve(cmd_plus_path, cmd_args_joined, environ) < 0)
	{
		ft_putstr_fd("failed at execve\n", 2);
		// printf("failed at execve\n");
		exit(EXIT_FAILURE);
	}
}
