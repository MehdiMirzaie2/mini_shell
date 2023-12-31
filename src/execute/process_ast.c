/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:48:49 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/14 17:45:31 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "shell.h"
#include <stdio.h>
#include <sys/wait.h>

void	get_command_name(char **dst, t_cmd *cmd, bool movearg)
{
	t_arglst	*old;
	char		*name;

	if (cmd == NULL)
		return ;
	name = NULL;
	if ((cmd->cmd == NULL || *cmd->cmd == '\0') && cmd->args != NULL)
	{
		name = cmd->args->str;
		if (movearg)
		{
			if (cmd->cmd || *cmd->cmd == '\0')
				free(cmd->cmd);
			old = cmd->args;
			cmd->args = cmd->args->next;
			old->next = NULL;
			old->dup = false;
			arglst_memman(&old, true);
		}
	}
	else
		name = cmd->cmd;
	if (dst && *dst != name)
		*dst = name;
}

void	process_ast(t_mshctx msh, t_env **our_env, int *exit_status)
{
	t_ast *const	ast = msh.ast;
	const int		in = dup(STDIN_FILENO);
	const int		out = dup(STDOUT_FILENO);
	int				num_cmds;
	pid_t			pid;

	if (ast->type == E_ASTCMD && is_envbuiltin(ast->cmd))
	{
		open_file(ast, NULL, 1, *our_env);
		*exit_status = execute_builtin_cmds(ast->cmd, our_env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		num_cmds = get_num_cmd(ast);
		execute(ast, our_env, &pid, num_cmds);
		if (waitpid(pid, exit_status, 0) != -1)
			num_cmds--;
		while (num_cmds--)
			wait(NULL);
	}
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}
