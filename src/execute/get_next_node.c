/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:15:27 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/25 18:14:22 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"

t_ast	*get_next_node(t_ast *ast, int num_cmds)
{
	static int		go_right = 0;
	static bool		checked_left = false;
	t_ast			*next_node;
	int				i;

	i = 0;
	next_node = NULL;
	if (!ast || ast->type == E_ASTCMD)
		return (ast);
	while (i++ < go_right)
		ast = ast->u_node.link.second;
	if (checked_left == false)
		return (checked_left = true, ast->u_node.link.first);
	if (ast->u_node.link.second->type == E_ASTCMD)
		next_node = ast->u_node.link.second;
	else
	{
		next_node = ast->u_node.link.second->u_node.link.first;
		checked_left = false;
		go_right++;
		checked_left = true;
	}
	if (num_cmds == 1)
		return (go_right = 0, checked_left = false, next_node);
	return (next_node);
}
