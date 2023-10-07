/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:54:17 by clovell           #+#    #+#             */
/*   Updated: 2023/10/07 17:24:19 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static void	get_append(char **format, va_list *list, char **tmp)
{
	char	fmt;

	if (**format == '%')
	{
		fmt = (*format)[1];
		if (fmt == '%')
			*tmp = "%";
		else if (fmt == 'd')
			*tmp = ft_itoa(va_arg(*list, int));
		else if (fmt == 'l')
			*tmp = ft_itoa(va_arg(*list, long long int));
		else if (fmt == 's' || fmt == 'S')
			*tmp = va_arg(*list, char *);
		else if (fmt == 'c')
			*tmp[0] = va_arg(*list, int);
		(*format)++;
	}
	else
		*tmp[0] = **format;
}

char	*ft_strfmt(char *fmt, ...)
{
	va_list		list;
	char		*buffer;
	char		*append;
	char		*old;
	char		charstr[2];

	buffer = ft_strdup("");
	va_start(list, fmt);
	charstr[1] = '\0';
	while (*fmt)
	{
		append = charstr;
		get_append(&fmt, &list, &append);
		old = buffer;
		buffer = ft_strjoin(old, append);
		free(old);
		if (*fmt == 'S' || *fmt == 'd' || *fmt == 'l')
			free(append);
		fmt++;
	}
	return (buffer);
}
