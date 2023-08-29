/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:06:15 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/29 13:23:59 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_echo(char *str, char *filename, int option)
{
	t_fd	fds;

	if (filename == NULL)
	{
		(void)filename;
		(void)fds;
		if (option == 1)
			ft_putstr_fd(ft_strtrim(str, "\n"), 1);
		else
		{
			ft_putstr_fd(str, 1);
			write(1, "\n", 1);
		}
	}
	else
	{
		fds = redirect_output(filename);
		if (option == 1)
			ft_putstr_fd(ft_strtrim(str, "\n"), fds.temp_out_in_fd);
		else
		{
			ft_putstr_fd(str, fds.temp_out_in_fd);
			write(fds.temp_out_in_fd, "\n", 1);
		}
		dup2(fds.saved_out_in_fd, STDOUT_FILENO);
		close(fds.saved_out_in_fd);
	}
}
