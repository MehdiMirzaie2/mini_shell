/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:25:09 by clovell           #+#    #+#             */
/*   Updated: 2023/09/07 02:07:25 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_extra.h"

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
