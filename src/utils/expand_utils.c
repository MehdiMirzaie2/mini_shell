/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:25:09 by clovell           #+#    #+#             */
/*   Updated: 2023/10/05 15:02:32 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extra.h"

static int	isenvstr(int c)
{
	return (c == '_' || ft_isalnum(c)); 
}

t_sd_stat	until_var_or_quote(char *str, int i, bool mode, void *ctx)
{
	char *const	quote = ctx;

	(void)mode;
	if (str[i] == '\0' || str[i] == *quote)
		return (E_SD_STOP);
	if (*quote != '\'' && str[i] == '$')
		return (E_SD_STOP);
	if (*quote != '\0' && (str[i] == '\'' || str[i] == '\"'))
		return (E_SD_STOP | E_SD_COPY);
	else if (str[i] == '\'' || str[i] == '\"')
		return (E_SD_STOP);
	return (E_SD_COPY);
}

t_sd_stat	until_var_end(char *str, int i, bool mode, void *ctx)
{
	(void)mode;
	(void)ctx;
	if (str[i] == '\0')
		return (E_SD_STOP);
	if (i == 1 && str[0] == '$' && str[1] == '?')
		return (E_SD_STOP | E_SD_COPY);
	if (str[i] != '$' && !isenvstr(str[i]))
		return (E_SD_STOP);
	if (i != 0 && str[i] == '$' && isenvstr(str[i + 1]))
		return (E_SD_STOP);
	return (E_SD_COPY);
}
/*
static t_sd_stat pass_quote_situ(char *str, int i, bool check, void *pctx)
{
	char	*depth = pctx;
	char	old;

	old = depth[check];
	if (str[i] == '\0')
		return (E_SD_STOP);
	if (str[i] == '\"' || str[i] == '\'')
	{
		if (depth[check] == '\0')
			depth[check] = str[i];
		else if (depth[check] == str[i])
			depth[check] = '\0';
		if (str[i] == old || depth[check] == str[i])
		    return (E_SD_SKIP);
	}
	return (E_SD_COPY);
}

t_sd_stat until_expandstr_end(char *str, int i, bool check, void *pctx)
{
	(void)check;
	(void)pctx;
	if (str[i] == '\0')
		return (E_SD_STOP);
	if (str[i] != '$' && !isenvstr(str[i]))
		return (E_SD_STOP);
	if (i != 0 && str[i] == '$' && isenvstr(str[i + 1]))
		return (E_SD_STOP);
	return (E_SD_COPY);
}

t_sd_stat until_expandstr_start(char *str, int i, bool check, void *pctx)
{
	int		*const depth = pctx;
	bool	expand;
	int		situ;

	situ = pass_quote_situ(str, i, check, pctx);
	if (situ != E_SD_COPY)
		return (situ);
	expand = depth[check] != '\'';
	if (expand && str[i] == '$' && isenvstr(str[i + 1]))
		return (E_SD_STOP);
	depth[2]++;
	return (E_SD_COPY);
}
*/
/*
int until_expandstr_end(int c)
{
	return (c != '_' && !ft_isalnum(c));
}

int until_expandstr_start(int c)
{
	return (c == '$' || c == '\0');
}

int	expandstr_split(int c)
{

	// Are we using this function?
	return (c == '\0' || c == '$' || ft_isspace(c));
}
*/
