/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:14:57 by clovell           #+#    #+#             */
/*   Updated: 2023/09/07 02:37:59 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"
#include "libft_extra.h"
#include "error.h"

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

char	*expand_str(char *str, t_env *env)
{
	char	*next;
	char	*expand;
	char	*any;
	char	*tmp;

	expand = ft_strdup("");
	any = NULL;
	while (true)
	{
		any = ft_strdupct(str, until_expandstr_start);
		str += ft_strlen(any);
		expand = ft_strfmt("%S%S", expand, any);
		if (ft_strchr(str, '$') != NULL)
		{
			tmp = ft_strdupct(&str[1], until_expandstr_end);
			next = env_get(env, tmp);
			str += ft_strlen(tmp) + 1;
			free(tmp);
			expand = ft_strfmt("%S%s", expand, next);
		}
		else
			break ;
	}
	return (expand);
}
