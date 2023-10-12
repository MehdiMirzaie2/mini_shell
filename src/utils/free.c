#include "shell.h"

void free_mshctx(t_mshctx ctx)
{
	if (ctx.env)
		free_envlist(ctx.env);
	if (ctx.ast)
		ast_memman(&ast, E_ASTLINK, true);
	if (ctx.lst)
		lst_destroy(lst);
	if (ctx.line)
		free(line);
	if (ctx.prompt)
		free(prompt);
}
