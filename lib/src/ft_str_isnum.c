/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:45:37 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/13 20:57:35 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool	ft_str_isnum(char *str)
{
	if (*str == '-' || *str == '+' || *str == ' ')
		++str;
	if(!(*str))
		return (false);
	while (*str)
	{
		if (*str == ' ')
			++str;
		if (*str == '\0')
			return (true);
		if (!ft_isdigit(*str))
			return (false);
		++str;
	}
	return (true);
}
