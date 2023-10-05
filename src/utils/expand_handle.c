/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:51:38 by clovell           #+#    #+#             */
/*   Updated: 2023/10/05 14:08:54 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*handle_single(char *str, char **expand)
{
	char	*any;

	str++;
	any = ft_strdupu(str, "\'");
	str += ft_strlen(any);
	*expand = ft_strfmt("%S%S", *expand, any);
	if (*str)
		str++;
	return (str);
}

char	*handle_var(char *str, char **expand, t_env *env)
{
	char	*key;
	char	*value;

	key = ft_strdupctx(str, NULL, until_var_end);
	value = env_get(env, &key[1]);
	str += ft_strlen(key);
	*expand = ft_strfmt("%S%s", *expand, value);
	return (str);
}

char	*handle_word(char *str, char quote, char **expand, t_env *env)
{
	char	*any;

	if (*str == '$')
		return (handle_var(str, expand, env));
	else
		any = ft_strdupctx(str, &quote, until_var_or_quote);
	str += ft_strlen(any);
	*expand = ft_strfmt("%S%S", *expand, any);
	return (str);
}

char	*handle_double(char *str, char quote, char **expand, t_env *env)
{
	str++;
	while (*str && *str != '\"')
	{
		str = handle_word(str, quote, expand, env);
	}
	if (*str)
		str++;
	return (str);
}