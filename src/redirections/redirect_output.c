/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:25:41 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/22 14:29:57 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	redirect_output(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "could not create: ", 18);
		ft_putstr_fd(filename, 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

// make sure that the file descriptor gets closed