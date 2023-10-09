/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:07:14 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/09 14:48:31 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <sys/wait.h>

static bool	is_last_cmd(int num_cmds)
{
	if (num_cmds == 1)
		return (true);
	return (false);
}

static void	open_and_redirect(char *name, int rw, int permission)
{
	int	file_fd;

	file_fd = 0;
	if (!permission)
		file_fd = open(name, rw, 0644);
	else
		file_fd = open(name, rw, permission);
	if (file_fd < 0)
		error_exit(ft_strfmt("%s: %s", name, "No such file or directory\n"), EXIT_FAILURE);
	if (!permission)
	{
		if (redirect(file_fd, STDIN_FILENO) < 0)
			error_exit(ft_strfmt("%s: %s", name, "No such file or directory\n"), EXIT_FAILURE);
	}
	else
		if (redirect(file_fd, STDOUT_FILENO) < 0)
			error_exit(ft_strfmt("%s: %s", name, "No such file or directory\n"), EXIT_FAILURE);
}

static void	open_file(t_ast *ast, int pipe1[2], int num_cmds)
{
	t_iolst	*redirects;

	redirects = ast->cmd->redirects;
	if (redirects == NULL)
	{
		if (is_last_cmd(num_cmds))
			return ;
		else
			redirect(pipe1[1], STDOUT_FILENO);
	}
	while (redirects)
	{
		if (redirects->type == E_TTLLA)
		{
			while (redirects->next)
				if (redirects->next->type == E_TTLLA)
					redirects = redirects->next;
			handle_heredoc(ast);
		}
		if (redirects->type == E_TTLA)
			open_and_redirect(redirects->str, O_RDONLY, 0);
		if (redirects->type == E_TTRA || redirects->type == E_TTRRA)
		{
			if (redirects->type == E_TTRA)
				open_and_redirect(redirects->str,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				open_and_redirect(redirects->str,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (!is_last_cmd(num_cmds))
			redirect(pipe1[1], STDOUT_FILENO);
		else
			if (pipe1)
				close(pipe1[1]);
		redirects = redirects->next;
	}
}

static void	execute(t_ast *ast, t_env **our_env, int *exit_status, int num_cmds)
{
	t_ast	*node;
	int		pipe1[2];

	while (num_cmds > 0)
	{
		node = get_next_node(ast, num_cmds);
		if (pipe(pipe1) < 0)
			perror("error making pipe\n");
		if (fork() == 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			open_file(node, pipe1, num_cmds);
			close(pipe1[0]);
			if (is_builtin(node->cmd) || is_envbuiltin(node->cmd))
				execute_builtin_cmds(node->cmd, our_env, exit_status);
			else
				execute_system_cmds(node->cmd, *our_env);
			exit(EXIT_SUCCESS);
		}
		redirect(pipe1[0], STDIN_FILENO);
		close(pipe1[1]);
		num_cmds--;
	}
}

void	process_ast(t_ast *ast, t_env **our_env, int *exit_status)
{
	const int	in = dup(STDIN_FILENO);
	const int	out = dup(STDOUT_FILENO);
	int			num_cmds;

	signal(SIGINT, SIG_IGN);
	if (ast->type == E_ASTCMD && (is_builtin(ast->cmd)
		|| is_envbuiltin(ast->cmd)))
	{
		open_file(ast, NULL, 1);
		execute_builtin_cmds(ast->cmd, our_env, exit_status);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		num_cmds = get_num_cmd(ast);
		init_termios();
		execute(ast, our_env, exit_status, num_cmds);
		reset_termios();
		while (num_cmds-- > 0)
			wait(exit_status);
	}
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}
