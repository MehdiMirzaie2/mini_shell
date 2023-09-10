/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:14:57 by clovell           #+#    #+#             */
/*   Updated: 2023/09/11 01:15:26 by clovell          ###   ########.fr       */
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

	// TODO: for redirections?
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
 *	~`any = until_expandstr_start` with ~`str += len(any)`
 *	Should usually result with str pointing to the START of a 'proper var'
 *	Improper vars and non-vars characters stop the duplication.
 *
 *	`strdupi` with `until_expandstr_end` returns the proper var name.
 */
char	*expand_str(char *str, t_env *env)
{
	char	*expand;

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
	char	*any;
	char	*tmp;
	char	*next;

	while (true)
	{
		any = ft_strdupi(str, until_expandstr_start);
		ft_assert(any == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		str += ft_strlen(any);
		expand = ft_strfmt("%S%S", expand, any);
		ft_assert(expand == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		if (ft_strchr(str, '$') == NULL)
			break ;
		tmp = ft_strdupi(str, until_expandstr_end);
		ft_assert(tmp == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		if (tmp[0] == '$')
			next = env_get(env, &tmp[1]);
		else
			next = env_get(env, tmp);
		str += ft_strlen(tmp);
		free(tmp);
		if (next != NULL)
			expand = ft_strfmt("%S%s", expand, next);
	}
	return (expand);
}
