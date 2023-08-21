/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:31:50 by clovell           #+#    #+#             */
/*   Updated: 2023/08/21 14:45:45 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_cmdast t_cmpast;
typedef struct s_parseinfo t_pinfo;
typedef enum e_epinfo	t_epinfo;

enum e_epinfo
{
	E_OKAY,
	E_INVALID_SYN,
	E_MISSING_TOK
};

struct s_parseinfo
{
	int			position;
	t_epinfo	info;
};

struct s_cmd 
{
	char *cmd;
	t_strlst *args;

	t_strlst *heredoc;
	t_strlst *strin;
	t_strlst *strout;
	t_strlst *strapp;
};

struct s_cmdast
{
	t_cmdast	*pipe;
	t_cmd		*first;
	t_cmd		*second;
	enum 
	{
		E_START,
		E_SINGLE,
		E_PIPE,
	} tag;
	union
	{
		t_cmdast *next;
		t_cmd *cmd;
		struct s_ast_pipe {t_cmdast *first; t_cmdast *second} pipe;
	}
};
/*if (type == E_LLA)
				target = cmd->heredoc;
			else if (target == E_RRA)
				target = cmd->stdapp;
				else if (type == E_LA)
				target = cmd->strin;
			else
				target = cmd->strout;
			s*/

t_cmd	*cmd_new()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = NULL;
	cmd->heredoc = NULL;
	cmd->strin = NULL;
	cmd->strout = NULL;
	cmd->strapp = NULL;
	return (cmd);
}

int cmd_set(t_token **tokenadv, t_cmd *cmd)
{
	t_strlst *const targets[] = 
	{cmd->strin, cmd->strout, cmd->heredoc, cmd->strapp};
	t_ttoken type;
	t_strlst *target;

	token = *tokenadv;
	while ((*token) != NULL && (*token)->type != E_P)
	{
		type = (*token)->type;
		if (type & (E_LA | E_RA | E_LLA | E_RRA))
		{
			if ((*token)->next == NULL)
				return ((t_error){(*token)->pos, E_MISSING_TOK});
			target = targets[get_token_index(type) - get_token_index(E_LA)];
			strlst_add((*token)->next->str, target);
			*tokenadv = (*token)->next->next;
			continue;
		}
		else if ((type == E_WD || (type & E_GS) != 0) && cmd->name == NULL)
			cmd->name = (*token)->str;
		else if (type == E_WD || (type & E_GS != 0))
			strlst_add((*token)->str, cmd->args);
		*token = (*token)->next;
	}
	return ({0, E_OKAY});
}

void	build_ast(t_cmlstast *ast, t_token *tokadv)
{
	const t_token *token = *tokadv;

	if (token == NULL)
		return ;
	if (ast->first == NULL)
		cmd_set(toknext(tokadv), *cmd);
	if (token->type == E_PIPE)
		build_ast_handle_pipe(ast, tokadv);
	if (type & (E_LA | E_RA | E_LLA | E_RRA))
		strlst_add((*token)->next->str, get_cmd_str_dst(cmd, token->type));
	if (type == E_WD)
}

/*
 *
 * USE CASE:
 * When a pipe is found and the current ast node is using both cmd slots.
 * move the second cmd slot to a new sub astnode that is in the first child.	
 * `next` will never be null, found by the tokeniser. (ast never build)
 echo "test" | <enter> <line read mode> <type>|<enter> (unexpected token)
 */
t_cmdast *build_ast_handle_pipe(t_cmdast *ast, token **tokadv)
{
	if (ast->first == NULL)
		ast->first = build_cmd(tokadv);
	else if (ast->second == NULL)
		ast->second = build_cmd(tokadv);
	else if (ast->second != NULL)
	{
		ast->pipe = empty_ast();
		ast->pipe->first = ast->second;
		ast->second = NULL;
		*tokadv = tokadv->next;
		build_ast(ast->pipe, tokadv);
	}
}

t_cmdast *ast_new()
{
	t_cmdast *ast;

	ast = malloc(sizeof(t_cmdast));
	ast->pipe = NULL;
	ast->first = NULL;
	ast->second = NULL;
	return (ast);
}

/*
 *
 * NOTE:
 * On failure it's up to the caller to free token list.
 */
t_cmdast *ast_create_tlst(t_token *curr)
{
	t_cmdast	*ast;
	t_cmd		*cmd;
	t_cmd		**target;

	t_pinfo		info;

	if (curr == NULL)
		return (NULL);
	if (curr->type == E_ALL)
		curr = lst->next;
	ast = ast_new();
	target = &ast->first;
	while (curr != NULL)
	{
		info = cmd_set(&curr, *cmd);
		if (info.info != E_OKAY)
			return (NULL); // RETURN CLEANUP
		if (curr != NULL)
			target = 
	}
	return (ast);
}
