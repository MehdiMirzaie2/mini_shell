/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:07:14 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/17 13:09:43 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <sys/wait.h>

static void	open_and_redirect(char *name, int rw, int permission)
{
	int	file_fd;

	file_fd = 0;
	file_fd = open(name, rw, 0644);
	if (file_fd < 0)
		error_exit(ft_strfmt("%s: %s", name, strerror(errno)), EXIT_FAILURE);
	if (!permission)
	{
		if (redirect(file_fd, STDIN_FILENO) < 0)
			error_exit(ft_strfmt("%s: %s", name,
					strerror(errno)), EXIT_FAILURE);
	}
	else
		if (redirect(file_fd, STDOUT_FILENO) < 0)
			error_exit(ft_strfmt("%s: %s", name,
					strerror(errno)), EXIT_FAILURE);
}

void	handle_cmdredirect(t_iolst *redirects,
	int pipe1[2], int num_cmds, t_env *env)
{
	const int		in = dup(STDIN_FILENO);
	const t_iolst	*start = redirects;

	while (start)
	{
		if (start && start->type == E_TTLLA)
			dup2(in, STDIN_FILENO);
		if (start && start->type == E_TTLLA)
			handle_heredoc((t_iolst *)start, env);
		start = start->next;
	}
	while (redirects)
	{
		if (redirects->type == E_TTLA)
			open_and_redirect(redirects->str, O_RDONLY, 0);
		if (redirects->type == E_TTRA)
			open_and_redirect(redirects->str, E_OUT, 0644);
		else if (redirects->type == E_TTRRA)
			open_and_redirect(redirects->str, E_APPEND, 0644);
		else if (num_cmds != 1)
			redirect(pipe1[1], STDOUT_FILENO);
		else if (pipe1)
			close(pipe1[1]);
		redirects = redirects->next;
	}
}

void	open_file(t_ast *ast, int pipe1[2], int num_cmds, t_env *env)
{
	t_iolst	*redirects;

	redirects = ast->cmd->redirects;
	if (redirects == NULL)
	{
		if (num_cmds == 1)
			return ;
		if (pipe1)
			redirect(pipe1[1], STDOUT_FILENO);
	}
	handle_cmdredirect(redirects, pipe1, num_cmds, env);
}

void	execute_child(t_ast *node, int pipe1[2], t_env **our_env, int num_cmds)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(pipe1[0]);
	open_file(node, pipe1, num_cmds, *our_env);
	if (!*node->cmd->cmd)
		exit(EXIT_SUCCESS);
	if (is_builtin(node->cmd) || is_envbuiltin(node->cmd))
		execute_builtin_cmds(node->cmd, our_env);
	else
		execute_system_cmds(node->cmd, *our_env);
	exit(EXIT_SUCCESS);
}

void	execute(t_ast *ast, t_env **our_env, int *latest_pid, int num_cmds)
{
	const int	in = dup(STDIN_FILENO);
	int			pipe1[2];
	pid_t		child;
	t_ast		*node;

	while (num_cmds > 0)
	{
		node = get_next_node(ast, num_cmds);
		loop_redirects(0, node->cmd->redirects, in);
		if (pipe(pipe1) < 0)
			perror("error making pipe\n");
		get_command_name(&node->cmd->cmd, node->cmd, true);
		child = fork();
		*latest_pid = child;
		if (child == 0)
			execute_child(node, pipe1, our_env, num_cmds);
		redirect(pipe1[0], STDIN_FILENO);
		close(pipe1[1]);
		num_cmds--;
		loop_redirects(child, node->cmd->redirects, 0);
	}
}
