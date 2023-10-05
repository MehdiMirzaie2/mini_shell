/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 02:47:59 by clovell           #+#    #+#             */
/*   Updated: 2023/10/05 14:19:20 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "cmd.h"
# include "lexer.h"

typedef struct s_ast		t_ast;
typedef enum e_asttype		t_asttype;
typedef enum e_astlinktype	t_astlinktype;
typedef struct s_astbuilder	t_astbuilder;

enum e_asttype
{
	E_ASTCMD,
	E_ASTLINK
};

enum e_astlinktype
{
	E_ASTLINKAND,
	E_ASTLINKOR,
	E_ASTLINKPIPE
};

struct s_astbuilder
{
	t_token	*thead;
	t_token	*current;

	t_ast	*head;
	t_ast	**work;
};

struct s_ast
{
	t_asttype	type;
	union
	{
		t_cmd	*cmd;
		struct s_astlink {
			t_ast			*first;
			t_ast			*second;
			t_astlinktype	type;
		} link;
	} u_node;
};

/* ast.c */
t_ast	*ast_build(t_token *tokens);
void	ast_memman(t_ast **ast, t_asttype type, bool destroy);

/* ast_builder.c */
void	astb_start(t_astbuilder *builder);
void	astb_addcmd(t_astbuilder *builder);
void	astb_branch(t_astbuilder *builder, t_astlinktype type);
void	astbuilder_memman(t_astbuilder **astb, bool destroy);

/* debug_ast.c */
void	tast_print(t_ast *ast);

// Should we use this struct instead to return an ast or an error?
// struct s_astinfo
// {
// 	enum {
// 		OKAY,
// 		ERROR
// 	} tag;
// 	union
// 	{
// 		t_ast *ast;
// 		char *error;
// 	};
// };
#endif
