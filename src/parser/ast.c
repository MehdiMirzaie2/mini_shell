#include <stdio.h>
#include "standard.h"
#include "ast.h"

t_ast	*ast_build(t_token *tokens)
{
	t_astbuilder	*builder;
	t_ast			*ast;

	astbuilder_memman(&builder, false);
	builder->thead = tokens;
	builder->current = tokens;
	ast_memman(&builder->head, E_ASTCMD, false);
	builder->work = &builder->head;
	astb_start(builder);
	ast = builder->head;
	astbuilder_memman(&builder, true);
	return (ast);
}

static void printtabs(unsigned int level)
{
	while(level--)
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

void	tast_printl(t_ast *ast, int level)
{
	if (ast->type == E_ASTLINK)
	{
		printtabs(level);
		printf("PIPE\n");
		printtabs(level + 1);
		printf("FIRST:\n");
		tast_printl(ast->u_node.link.first, level + 2);
		printtabs(level + 1);
		printf("SECOND:\n");
		tast_printl(ast->u_node.link.second, level + 2);
	}
	else
	{
		printtabs(level);
		printf("CMD: ");
		printf("%s\n", ast->u_node.cmd->cmd);
		t_arglst *lst = ast->u_node.cmd->args;
		if (lst != NULL)
		{
			printtabs(level);
			printf("ARGS ");
			while (lst)
			{
				printf("\"%s\" ", lst->str);
				lst = lst->next;
			}
			printf("\n");
		}
		tiolst_print(ast->u_node.cmd->heredoc, "HEREDOC ", level);
		tiolst_print(ast->u_node.cmd->strin, "STRIN ", level);
		tiolst_print(ast->u_node.cmd->strout, "STROUT ", level);
		tiolst_print(ast->u_node.cmd->strapp, "STRAPP ", level);
	}
}

void tast_print(t_ast *ast)
{
	tast_printl(ast, 0);
}


void	ast_memman(t_ast **ast, t_asttype type, bool destroy)
{
	const t_ast builder = {.type = type};
	
	if (!destroy)
	{
		*ast = malloc(sizeof(t_ast));
		if (*ast == NULL)
			ft_errx(E_MALLOCFAIL, E_MSG_AST_MALLOC, __FILE__, __LINE__);
		**ast = builder;
		if (type == E_ASTCMD)
			cmd_memman(&(*ast)->u_node.cmd, false);
	}
	else
	{
		if (*ast == NULL)
			return ;
		if ((*ast)->type == E_ASTCMD)
			cmd_memman(&(*ast)->u_node.cmd, true);
		else
		{
			ast_memman(&(*ast)->u_node.link.first, E_ASTCMD, true);
			ast_memman(&(*ast)->u_node.link.second, E_ASTCMD, true);
		}
		free(*ast);
	}
}
