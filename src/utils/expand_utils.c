/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:25:09 by clovell           #+#    #+#             */
/*   Updated: 2023/09/10 20:25:04 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_extra.h"


static int	isenvstr(int c)
{
	return (c == '_' || ft_isalnum(c));
}

int until_expandstr_end(char *str, int i)
{
	if (str[i] != '$' && !isenvstr(str[i]))
		return (2);
	if (i != 0 && str[i] == '$' && isenvstr(str[i + 1]))
		return (2);
	return (1);
}

int until_expandstr_start(char *str, int i)
{
	if (str[i] == '\0')
		return (2);
	if (str[i] == '$' && isenvstr(str[i + 1]))
		return (2);
	return (1);
}
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
