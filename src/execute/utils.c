/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:41:38 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/09/20 15:12:23 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	is_builtin(char	*cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "$?", 2) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "exit", 4))
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
		ast = ast->u_node.link.second;
		num++;
	}
	return (num);
}

int	get_num_args(t_cmd *cmd)
{
	int	num;
	t_arglst	*ref_args;
	// t_cmd	*ref_cmd;

	ref_args = cmd->args;
	num = 0;
	while (ref_args)
	{
		ref_args = ref_args->next;
		num++;
	}
	// ref_cmd = cmd;
	return (num);
}