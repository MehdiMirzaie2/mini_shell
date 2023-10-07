/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 08:04:43 by clovell           #+#    #+#             */
/*   Updated: 2023/10/07 16:21:05 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdio.h>

static void	printtabs(unsigned int level)
{
	while (level--)
	{
		printf("    ");
	}
}

static void	tiolst_print(t_iolst *lst, int level)
{
	if (lst != NULL)
	{
		printtabs(level);
		while (lst)
		{
			if (lst->type == E_TTLA)
				printf("STDIN:(");
			if (lst->type == E_TTLLA)
				printf("HEREDOC:(");
			if (lst->type == E_TTRA)
				printf("STDOUT:(");
			if (lst->type == E_TTRRA)
				printf("STDAPP:(");
			printf("\"%s\"), ", lst->str);
			lst = lst->next;
		}
		printf("\n");
	}
}
static void	tast_printl(t_ast *ast, int level);

static void	tast_cmdprint(t_ast *ast, int level)
{
	printf("PIPE\n");
	printtabs(level + 1);
	printf("FIRST:\n");
	tast_printl(ast->u_node.link.first, level + 2);
	printtabs(level + 1);
	printf("SECOND:\n");
	tast_printl(ast->u_node.link.second, level + 2);
}

static void	tast_printl(t_ast *ast, int level)
{
	t_arglst	*lst;

	printtabs(level);
	if (ast->type == E_ASTLINK)
		tast_cmdprint(ast, level);
	else
	{
		printf("CMD %s\n", ast->u_node.cmd->cmd);
		lst = ast->u_node.cmd->args;
		if (lst != NULL)
		{
			printtabs(level);
			printf("ARGS ");
			while (lst)
			{
				printf("\"%s\" ", lst->str);
				lst = lst->next;
			}
		}
		tiolst_print(ast->u_node.cmd->redirects, level);
	}
}

void	tast_print(t_ast *ast)
{
	tast_printl(ast, 0);
	printf("\n");
}
