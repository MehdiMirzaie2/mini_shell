/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:13:56 by clovell           #+#    #+#             */
/*   Updated: 2023/10/11 01:35:03 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include "libft.h"

void	ft_printf_fd(int fd, char *fmt, ...)
{
	int		tmp;
	va_list	lst;

	va_start(lst, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == 'i' || *fmt == 'd')
				ft_putnbr_fd(va_arg(lst, int), fd);
			else if (*fmt == 's')
				ft_putstr_fd(va_arg(lst, char *), fd);
			else if (*fmt == 'c')
			{
				tmp = va_arg(lst, int);
				write(fd, &tmp, 1);
			}
		}
		else
			write(fd, fmt, 1);
		fmt++;
	}
	va_end(lst);
}
