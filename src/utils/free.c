/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:47:27 by clovell           #+#    #+#             */
/*   Updated: 2023/10/13 10:47:50 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "ast.h"

void	free_mshctx(t_mshctx ctx)
{
	if (ctx.env)
		free_env(ctx.env, true);
	if (ctx.ast)
		ast_memman(&ctx.ast, E_ASTLINK, true);
	if (ctx.lst)
		tlst_destroy(ctx.lst);
	if (ctx.line)
		free(ctx.line);
	if (ctx.prompt)
		free(ctx.prompt);
}

int	free_strarr(char **array)
{
	char	**start;

	if (array == NULL)
		return (0);
	start = array;
	while (*start != NULL)
	{
		free(*start);
		start++;
	}
	free(array);
	return (0);
}
