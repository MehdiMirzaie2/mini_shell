/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:07:14 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/03 22:00:18 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <sys/wait.h>

bool	is_last_cmd(int num_cmds, int pipe1[2])
{
	if (num_cmds == 1)
		return (true);
	redirect(pipe1[1], STDOUT_FILENO);
	return (false);
}

void	open_and_redirect(char *name, int rw, int permission)
{
	int	file_fd;

	if (!permission)
		file_fd = open(name, rw);
	else
		file_fd = open(name, rw, permission);
	if (file_fd < 0)
		error_exit(" No such file or directory\n", EXIT_FAILURE);
	if (!permission)
	{
		if (redirect(file_fd, STDIN_FILENO) < 0)
			error_exit(" No such file or directory\n", EXIT_FAILURE);
	}
	else
		if (redirect(file_fd, STDOUT_FILENO) < 0)
			error_exit(" No such file or directory\n", EXIT_FAILURE);
}

void	open_file(t_ast *ast, int pipe1[2], int num_cmds)
{
	int		file_fd;
	t_iolst	*ref_redirects;

	ref_redirects = ast->u_node.cmd->redirects;
	if (ref_redirects == NULL)
		if (is_last_cmd(num_cmds, pipe1))
			return ;
	while (ref_redirects)
	{
		if (ref_redirects->type == E_TTLLA)
			handle_heredoc(ast);
		if (ref_redirects->type == E_TTLA)
		{
			file_fd = open(ref_redirects->str, O_RDONLY);
			if (redirect(file_fd, STDIN_FILENO) < 0)
				error_exit(" No such file or directory\n", EXIT_FAILURE);
		}
		if (ref_redirects->type == E_TTRA
			|| ref_redirects->type == E_TTRRA)
		{
			if (ref_redirects->type == E_TTRA)
				file_fd = open(ref_redirects->str,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				file_fd = open(ref_redirects->str,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file_fd < 0)
				error_exit(" No such file or directory\n", EXIT_FAILURE);
			redirect(file_fd, STDOUT_FILENO);
			close(pipe1[1]);
		}
		// else
		// 	if (is_last_cmd(num_cmds, pipe1))
		// 		return ;
		ref_redirects = ref_redirects->next;
	}
}

void	execute(t_ast *ast_node, t_env **our_env, int *exit_status)
{
	if (is_builtin(ast_node->u_node.cmd) || is_envbuiltin(ast_node->u_node.cmd))
		execute_builtin_cmds(ast_node->u_node.cmd, our_env, exit_status);
	else
		execute_system_cmds(ast_node->u_node.cmd, *our_env);
}

void	create_childs(t_ast *node, int pipe1[2], t_env **our_env, int *exit_status, int num_cmds)
{
	open_file(node, pipe1, num_cmds);
	close(pipe1[0]);
	execute(node, our_env, exit_status);
	exit(EXIT_SUCCESS);
}

void	process_ast(t_ast *ast, t_env **our_env, int *exit_status)
{
	t_ast		*next_ast_node;
	int			pipe1[2];
	int			i;
	int			num_cmds;
	const int	in = dup(STDIN_FILENO);
	t_cmd		*first_cmd;

	if (ast->type == E_ASTCMD)
		first_cmd = ast->u_node.cmd;
	else
		first_cmd = ast->u_node.link.first->u_node.cmd;
	if (is_envbuiltin(first_cmd))
	{
		open_file(ast, NULL, 1);
		execute_builtin_cmds(ast->u_node.cmd, our_env, exit_status);
		ast = ast->u_node.link.second;
	}
	num_cmds = get_num_cmd(ast);
	i = num_cmds;
	while (num_cmds > 0)
	{
		next_ast_node = get_next_node(ast, num_cmds);
		if (pipe(pipe1) < 0)
			perror("error making pipe\n");
		if (fork() == 0)
			create_childs(next_ast_node, pipe1, our_env, exit_status, num_cmds);
		// if (fork() == 0)
		// {
		// 	open_file(next_ast_node, pipe1, num_cmds);
		// 	close(pipe1[0]);
		// 	execute(next_ast_node, our_env, exit_status);
		// 	exit(EXIT_SUCCESS);
		// }
		if (--num_cmds > 0)
		{
			if (dup2(pipe1[0], STDIN_FILENO) < 0)
				perror("dup to pipe1[0] error\n");
			close(pipe1[0]);
			close(pipe1[1]);
			if (pipe(pipe1) < 0)
				perror("error makeing pipe\n");
			next_ast_node = get_next_node(ast, num_cmds);
			if (fork() == 0)
			{
				open_file(next_ast_node, pipe1, num_cmds);
				close(pipe1[0]);
				execute(next_ast_node, our_env, exit_status);
				exit(EXIT_SUCCESS);
			}
		}
		if (dup2(pipe1[0], STDIN_FILENO) < 0)
			perror("dup to pipe1[0] error\n");
		close(pipe1[0]);
		close(pipe1[1]);
		num_cmds--;
	}
	while (i-- > 0)
	{
		wait(exit_status);
		// if (*exit_status != 0)
		// while (i-- > 0)
		// 	wait(NULL);
	}
	dup2(in, STDIN_FILENO);
}
//clearing standard in; important
