/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:36:41 by clovell           #+#    #+#             */
/*   Updated: 2023/03/14 14:49:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

static void	ft_putnbr_r(unsigned int nbr, int fd)
{
	char	c;

	if (nbr > 0)
	{
		ft_putnbr_r(nbr / 10, fd);
		c = nbr % 10 + '0';
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	un = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		un = -n;
	}
	ft_putnbr_r(un, fd);
}
