/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:14:57 by clovell           #+#    #+#             */
/*   Updated: 2023/10/11 16:08:03 by clovell          ###   ########.fr       */
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
		ast_expandall(ast->link.first, env);
		ast_expandall(ast->link.second, env);
	}
	else
		cmd_expand(ast->cmd, env);
}

static void	args_redirect_expand(t_arglst *arg, t_iolst *lst, t_env *env);

void	cmd_expand(t_cmd *cmd, t_env *env)
{
	char		*tmp;

	tmp = cmd->cmd;
	if (cmd->cmd)
		cmd->cmd = expand_str(cmd->cmd, env);
	if (cmd->cmd != tmp)
		free(tmp);
	args_redirect_expand(cmd->args, cmd->redirects, env);
}

static void	args_redirect_expand(t_arglst *arg, t_iolst *lst, t_env *env)
{
	char	*tmp;

	while (arg)
	{
		tmp = arg->str;
		arg->str = expand_str(arg->str, env);
		ft_assert(tmp != NULL && arg->str == NULL,
			E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		if (tmp != arg->str && arg->dup)
			free(tmp);
		arg = arg->next;
	}
	while (lst)
	{
		tmp = lst->str;
		lst->str = expand_str(lst->str, env);
		ft_assert(tmp != NULL && lst->str == NULL,
			E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		if (tmp != lst->str && lst->dup)
			free(tmp);
		lst = lst->next;
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
	char	mode;

	while (*str)
	{
		mode = '\0';
		if (*str == '\'' || *str == '\"')
			mode = *str;
		if (*str == '\"')
			str = handle_double(str, mode, &expand, env);
		else if (*str == '\'')
			str = handle_single(str, &expand);
		else
			while (*str && (*str != '\'' && *str != '\"'))
				str = handle_word(str, mode, &expand, env);
	}
	return (expand);
}
