/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:48:49 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/11 12:34:54 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <sys/wait.h>

void	process_ast(t_ast *ast, t_env **our_env, int *exit_status)
{
	const int	in = dup(STDIN_FILENO);
	const int	out = dup(STDOUT_FILENO);
	int			num_cmds;
	pid_t		*pids;

	if (ast->type == E_ASTCMD && is_envbuiltin(ast->cmd))
	{
		open_file(ast, NULL, 1);
		execute_builtin_cmds(ast->cmd, our_env, exit_status);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		num_cmds = get_num_cmd(ast);
		execute(ast, our_env, exit_status, num_cmds);
		(void)pids;
		while (num_cmds-- > 0)
			wait(exit_status);
	}
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}
