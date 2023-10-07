/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:41:38 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/03 22:05:17 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	is_builtin(t_cmd *cmd)
{
	char	*command;

	if (!cmd)
		return (false);
	command = cmd->cmd;
	if (!ft_strncmp(command, "echo", 4) || !ft_strncmp(command, "exit", 4))
		return (true);
	return (false);
}

bool	is_envbuiltin(t_cmd	*cmd)
{
	char	*command;

	if (!cmd)
		return (false);
	command = cmd->cmd;
	if (!ft_strncmp(command, "cd", 2) || !ft_strncmp(command, "env", 3)
		|| !ft_strncmp(command, "pwd", 3) || !ft_strncmp(command, "export", 6)
		|| !ft_strncmp(command, "unset", 5))
		return (true);
	return (false);
}

int	redirect(int from, int to)
{
	if (dup2(from, to) == -1)
		return (-1);
	if (close(from) == -1)
		return (-1);
	return (0);
}

int	get_num_cmd(t_ast *ast)
{
	int	num;

	num = 0;
	while (ast)
	{
		ast = ast->link.second;
		num++;
	}
	return (num);
}

int	get_num_args(t_cmd *cmd)
{
	int			num;
	t_arglst	*ref_args;

	ref_args = cmd->args;
	num = 0;
	while (ref_args)
	{
		ref_args = ref_args->next;
		num++;
	}
	return (num);
}
