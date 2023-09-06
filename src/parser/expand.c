/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:14:57 by clovell           #+#    #+#             */
/*   Updated: 2023/09/06 20:05:31 by clovell          ###   ########.fr       */
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

static char	*expand_str_replace(char *str, t_env *env)
{
	char	*value;

	value = expand_str(str, env);
	if (value != str)
		free(str);
	return (value);
}

void	cmd_expand(t_cmd *cmd, t_env *env)
{
	t_arglst	*arg;

	// TODO: for redirections?
	cmd->cmd = expand_str_replace(cmd->cmd, env);
	arg = cmd->args;
	while (arg)
	{
		if (arg->expand && arg->dup)
			arg->str = expand_str_replace(arg->str, env);
		else if (arg->expand)
			arg->str = expand_str(arg->str, env);
		arg = arg->next;
	}
}

//int	get_expandstr_info(char *str, char **value, char **name, t_env *env)
//{
//    int	i;

//    i = 0;
//    if (str == NULL)
//        return (-1);
//    if (str[0] == '\'')
//        return (-1);
//    while (str[i] && str[i] != '$')
//        i++;
//    if (str[i] == '\0')
//        return (-1);
//    *name = ft_strdupct(&str[i + 1], expandstr_split);
//    if (*name == NULL)
//        ft_errx(E_MALLOCFAIL, E_MSG_STRDUP_MALLOC, __FILE__, __LINE__);
//    if (**name == '\0')
//        return (-1);
//    if (**name == '$')
//        *value = env_get(env, &(*name)[1]);
//    else
//        *value = env_get(env, *name);
//    if (*value == NULL)
//        *value = ft_strdup("");
//    return (i);
//}

/*
 * i/start:	Start of where the variable begins.
 * len 0:	string length of 'str'
 * len 1:	string length of 'name'
 * len 2:	string length of 'value'
 *
 * len 3:	('str' - 'name') + 'value' ---
 * 			the new total string length
 *
 * len 4:	('str' - ('start' + 'name')) ---
 * 			the letter count after the variable.
 *
 */
//char	*expand_str(char *str, t_env *env)
//{
//    char	*name;
//    char	*value;
//    char	*expand;
//    int		len[5];
//    int		i;

//    i = 0;
//    expand = ft_strdup(str);
//    while (ft_strchr(str[i], '$'))
//    {
//        i = get_expandstr_info(&expand[i], &value, &name, env);
//        if (i == -1)
//            return (expand);
//        len[0] = ft_strlen(str);
//        len[1] = ft_strlen(name);
//        len[2] = ft_strlen(value);
//        len[3] = len[0] - len[1] + len[2] + 1;
//        len[4] = len[0] - (i + len[1]) + 1;
//        free(expand);
//        expand = ft_calloc(1, len[3]);
//        ft_strlcat(expand, str, i + 1);
//        ft_strlcat(&expand[i], value, len[2] + 1);
//        ft_strlcat(&expand[i + len[2]], &str[i + len[1]], len[4]);
//        free(name);
//    }
//    return (expand);
//}


//char *expand(char *str, t_env *env)
//{
//    char *start;
//    char *end;

//    char *expand;
//    char *tmp;
	
//    expand = ft_strdup("");
//    start = str;
//    while (start)
//    {
//        start = ft_strchr(start, '$');
//        if (start != NULL)
//        {
//            tmp = try_env_get(start, end, env);
//            if (tmp == NULL)
//                continue ;
//            end = ft_strdupu(end, "$");
//            if (end == NULL)
//            {
//                end = &start[1];
//                while (isexpandable(end))
//                    end++;
//            }
//            expand = ft_strfmt("%S%S%S", expand, tmp, end);
//        }
//        else
//            expand = ft_strfmt("%S", expand, end);
//    }
//    return (expand);
//}


char *expand_str(char *str, t_env *env)
{
	char	*next;
	char	*expand;
	char	*any;
	char	*tmp;
	bool	avail;

	expand = ft_strdup("");
	avail = true;
	next = NULL;
	while (avail)
	{
		if (ft_strchr(str, '$') == NULL)
			avail = false;
		any = ft_strdupct(str, until_expandstr_start);
		str += ft_strlen(any);
		if (avail)
		{
			tmp = ft_strdupct(&str[1], until_expandstr_end);
			next = env_get(env, tmp);
			str += ft_strlen(tmp) + 1;
			free(tmp);
		}
		if (next != NULL)
			expand = ft_strfmt("%S%S%s", expand, any, next);
		else
			expand = ft_strfmt("%S%S", expand, any);
	}
	return (expand);
}
