/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:13:12 by clovell           #+#    #+#             */
/*   Updated: 2023/10/10 17:51:24 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ast.h"
#include "lexer.h"



static int	astb_addcmd(t_astbuilder *builder)
{
	t_ttoken		type;
	t_astlinktype	link;

	if (cmd_build((*builder->work)->cmd, &builder->current))
		return (1);
	if (builder->current == NULL)
		return (0);
	type = builder->current->type;
	if (type == E_TTNCP)
		link = E_ASTLINKPIPE;
	else if (type == E_TTNCA)
		link = E_ASTLINKAND;
	else if (type == E_TTNCO)
		link = E_ASTLINKOR;
	else
		return (0);
	builder->current = builder->current->next;
	astb_branch(builder, link);
	ast_memman(builder->work, E_ASTCMD, false);
	return (0);
}

/* Assumes builder->work to be allocated but empty. */
int	astb_start(t_astbuilder *builder)
{
	while (builder->current != NULL)
		if (astb_addcmd(builder))
			return (1);
	return (0);
}
/* Branches the current ast into two seperate sub trees
 * type: (E_TTP or E_TTAND or E_TTOR)
 *
 *	LEGEND:
 *	- parent
 *	+ child
 *	cat test.txt | wc -c
 *
 *	START
 *		CMD+-
 *	------- TURNS INTO --------\
 *	STAR
 *		PIPE-
 *			CMD
 *			CMD+
 */
void	astb_branch(t_astbuilder *builder, t_astlinktype type)
{
	t_ast	*latest;

	latest = *builder->work;
	if (latest->type == E_ASTCMD)
		latest->cmd->has_redirect = true;
	ast_memman(builder->work, E_ASTLINK, false);
	(*builder->work)->link.first = latest;
	(*builder->work)->link.type = type;
	builder->work = &(*builder->work)->link.second;
}

void	astbuilder_memman(t_astbuilder **astb, bool destroy)
{
	const t_astbuilder	builder = {0};

	if (!destroy)
	{
		*astb = malloc(sizeof(t_astbuilder));
		ft_assert(*astb == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		**astb = builder;
	}
	else
	{
		free(*astb);
		*astb = NULL;
	}
}
