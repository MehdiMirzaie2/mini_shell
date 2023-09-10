/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:13:12 by clovell           #+#    #+#             */
/*   Updated: 2023/09/09 20:46:12 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ast.h"
#include "lexer.h"

/* Assumes builder->work to be allocated but empty. */
void	astb_start(t_astbuilder *builder)
{
	while (builder->current != NULL)
		astb_addcmd(builder);
}

void	astb_addcmd(t_astbuilder *builder)
{
	t_ttoken		type;
	t_astlinktype	link;

	cmd_build((*builder->work)->u_node.cmd, &builder->current);
	if (builder->current == NULL)
		return ;
	type = builder->current->type;
	if (type == E_TTNCP)
		link = E_ASTLINKPIPE;
	else if (type == E_TTNCA)
		link = E_ASTLINKAND;
	else if (type == E_TTNCO)
		link = E_ASTLINKOR;
	else
		return ;
	builder->current = builder->current->next;
	astb_branch(builder, link);
	ast_memman(builder->work, E_ASTCMD, false);
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
	ast_memman(builder->work, E_ASTLINK, false);
	(*builder->work)->u_node.link.first = latest;
	(*builder->work)->u_node.link.type = type;
	builder->work = &(*builder->work)->u_node.link.second;
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
