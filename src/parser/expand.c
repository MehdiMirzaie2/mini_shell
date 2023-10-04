/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:14:57 by clovell           #+#    #+#             */
/*   Updated: 2023/10/03 23:51:35 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include "libft_extra.h"
#include "error.h"

static char	*unproc_expand_str(char *str, t_env *env, char *expand);

void	ast_expandall(t_ast *ast, t_env *env)
{
	if (ast == NULL)
		return ;
	if (ast->type == E_ASTLINK)
	{
		ast_expandall(ast->u_node.link.first, env);
		ast_expandall(ast->u_node.link.second, env);
	}
	else
		cmd_expand(ast->u_node.cmd, env);
}

void	cmd_expand(t_cmd *cmd, t_env *env)
{
	t_arglst	*arg;
	char		*tmp;

	// TODO: Do for redirections using cmd->redirects after mehdi:redirects2.0 is finished
	tmp = cmd->cmd;
	cmd->cmd = expand_str(cmd->cmd, env);
	if (cmd->cmd != tmp)
		free(tmp);
	arg = cmd->args;
	while (arg)
	{
		if (arg->expand)
		{
			tmp = arg->str;
			arg->str = expand_str(arg->str, env);
			if (tmp != arg->str && arg->dup)
				free(tmp);
		}
		arg = arg->next;
	}
}

/*
 * IMPLEMENTATION NOTES:
 *
 *	a proper (named) vars (env) can be defined as $[_A-Za-z0-9]*
 *	an in-proper var can be defined as $![_A-Za-z0-9]* (notice !)
 *
 *	So proper vars are variables that have valid name for environment variables
 *	and an improper var is a variable that has an invalid name.
 *
 *	improper vars are passed through and are not discarded.
 *	For example: echo $. #prints '$.' (. is not _, A-Z, a-z or 0-90)
 *
 *  unproc_expand_str:
 * TODO: Write description
 */
char	*expand_str(char *str, t_env *env)
{
	char		*expand;

	expand = ft_strdup("");
	ft_assert(str == NULL, E_ERR_BADPARAM, __FILE__, __LINE__);
	ft_assert(env == NULL, E_ERR_BADPARAM, __FILE__, __LINE__);
	ft_assert(expand == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
	expand = unproc_expand_str(str, env, expand);
	return (expand);
}


/* Assume valid inputs.
 * SEE:expand_str
 */
static char	*unproc_expand_str(char *str, t_env *env, char *expand)
{
	char mode;

	while (*str)
	{
		mode = '\0';
		if (*str == '\'' || *str == '\"')
			mode = *str;
		if (*str == '\"')
			str = handle_double(str, mode, &expand, env);
		else if (*str == '\'')
			str = handle_single(str, &expand);
		else while (*str && (*str != '\'' && *str != '\"'))
			str = handle_word(str, mode, &expand, env);
	}
	return (expand);
}
