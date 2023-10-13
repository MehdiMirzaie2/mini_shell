/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:13:56 by clovell           #+#    #+#             */
/*   Updated: 2023/10/13 12:18:11 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include "libft.h"

static void	handle_case(char *fmt, int fd, va_list *lst)
{
	int		tmp;
	char	*str;

	if (*fmt == 'i' || *fmt == 'd')
		ft_putnbr_fd(va_arg(*lst, int), fd);
	else if (*fmt == 's' || *fmt == 'S')
	{
		str = va_arg(*lst, char *);
		if (str != NULL)
		{
			ft_putstr_fd(str, fd);
			if (*fmt == 'S')
				free(str);
		}
		else
			write(fd, "(null)", 6);
	}
	else if (*fmt == 'c')
	{
		tmp = va_arg(*lst, int);
		write(fd, &tmp, 1);
	}
	else if (*fmt == '%')
		write(fd, "%", 1);
}

void	ft_printf_fd(int fd, char *fmt, ...)
{
	va_list	lst;

	va_start(lst, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			handle_case(fmt, fd, &lst);
		}
		else
			write(fd, fmt, 1);
		fmt++;
	}
	va_end(lst);
}
