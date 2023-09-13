/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 08:04:43 by clovell           #+#    #+#             */
/*   Updated: 2023/09/13 16:27:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "ast.h"

static void	printtabs(unsigned int level)
{
	while (level--)
	{
		printf("    ");
	}
}

static void	tiolst_print(t_iolst *lst, char *name, int level)
{
	if (lst != NULL)
	{
		printtabs(level);
		printf("%s", name);
		while (lst)
		{
			printf("\"%s\" ", lst->str);
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
		if (ast->u_node.cmd->has_redirect)
			printf("+has_redirect\n");
		if (ast->u_node.cmd->has_pipe)
			printf("+has_pipe\n");
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
		tiolst_print(ast->u_node.cmd->heredoc, "\nHEREDOC ", level);
		tiolst_print(ast->u_node.cmd->strin, "STRIN ", level);
		tiolst_print(ast->u_node.cmd->strout, "STROUT ", level);
		tiolst_print(ast->u_node.cmd->strapp, "STRAPP ", level);
	}
}

void	tast_print(t_ast *ast)
{
	tast_printl(ast, 0);
	printf("\n");
}
