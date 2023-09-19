/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:15:27 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/15 22:01:30 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"

t_ast	*get_next_node(t_ast *ast, bool reset)
{
	static int		go_right = 0;
	static bool		checked_left = false;
	static bool		is_recursive = false;
	// static bool		checked_all = false;
	t_ast			*next_node = NULL;
	int				i;

	i = 0;
	if (!ast)
		return (NULL);
	// if (checked_all == true)
	// 	return (NULL);
	if (ast->type == E_ASTCMD)
		return (ast);
	if (is_recursive == false)
	{
		while (i < go_right)
		{
			ast = ast->u_node.link.second;
			i++;
		}
	}
	if (checked_left == false)
	{
		next_node = ast->u_node.link.first;
		checked_left = true;
		// ft_putnbr_fd(getpid(), 2);
		// ft_putstr_fd(" returing: ", 2);
		// ft_putstr_fd(next_node->u_node.cmd->cmd, 2);
		// ft_putstr_fd("\n", 2);
		// return (next_node);
	}
	else
	{
		if (ast->type == E_ASTCMD)
			return (NULL);
		if (ast->type == E_ASTLINK)
		{
			if (ast->u_node.link.second->type == E_ASTCMD)
				next_node = ast->u_node.link.second;
			else{
				ast = ast->u_node.link.second;
				checked_left = false;
				is_recursive = true;
				go_right++;
				next_node = ast->u_node.link.first;
				checked_left = true;	
			}
			// get_next_node(ast);
		}
		// next_node = ast->u_node.link.second;
		// checked_all = true;
	}
	is_recursive = false;
	if (reset)
	{
		go_right = 0;
		checked_left = false;
		is_recursive = false;
	}
	// ft_putnbr_fd(getpid(), 2);
	// ft_putstr_fd(" returing: ", 2);
	// ft_putstr_fd(next_node->u_node.cmd->cmd, 2);
	// ft_putstr_fd("\n", 2);

	return (next_node);
}
