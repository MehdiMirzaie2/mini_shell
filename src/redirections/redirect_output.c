/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:25:41 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/23 12:54:57 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
// #include "libft.h"

// t_fd	redirect_output(char *filename)
// {
// 	// int	fd;
// 	// int saved_stdout
// 	t_fd fds;
	
// 	fds.saved_out_in_fd = dup(1);
// 	fds.temp_out_in_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fds.temp_out_in_fd == -1)
// 	{
// 		write(2, "could not create: ", 18);
// 		ft_putstr_fd(filename, 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fds.temp_out_in_fd, STDOUT_FILENO);
// 	return (fds);
// }

// int	redirect_output(char *filename)
// {
// 	int	fd;
// 	int saved_stdout

// 	saved_stdout = dup(1);
// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		write(2, "could not create: ", 18);
// 		ft_putstr_fd(filename, 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fd, STDOUT_FILENO);
// 	return (fd);
// }

// make sure that the file descriptor gets closed