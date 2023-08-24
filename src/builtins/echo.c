/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:06:15 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/21 11:14:03 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_echo(char *str, char *filename, int option)
{
	int	fd;

	if (filename == NULL)
	{
		(void)filename;
		(void)fd;
		if (option == 1)
			ft_putstr_fd(ft_strtrim(str, '\n'), 1);
		else
			ft_putstr_fd(str, 1);
	}
	else
	{
		fd = redirect_output(filename);
		if (option == 1)
			ft_putstr_fd(ft_strtrim(str, '\n'), fd);
		else
			ft_putstr_fd(str, fd);
		close(fd);
	}
}
