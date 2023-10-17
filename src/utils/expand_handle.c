/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:51:38 by clovell           #+#    #+#             */
/*   Updated: 2023/10/17 11:09:47 by clovell          ###   ########.fr       */
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
	if (ft_strlen(key) >= 2)
	{
		value = env_get(env, &key[1]);
		str += ft_strlen(key);
		if (value != NULL)
			*expand = ft_strfmt("%S%s", *expand, value);
	}
	else
	{
		str++;
		*expand = ft_strfmt("%S%s", *expand, "$");
	}
	free(key);
	return (str);
}

char	*handle_word(char *str, char quote, char **expand, t_env *env)
{
	char	*any;

	if (*str == '$')
		return (handle_var(str, expand, env));
	else
		any = ft_strdupctx(str, &quote, until_var_or_quote);
	if (*str == '~')
	{
		free(any);
		str++;
		any = ft_strdup(get_home(env));
	}
	else
		str += ft_strlen(any);
	if (any)
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
