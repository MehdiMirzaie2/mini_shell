/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:19:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/22 14:30:43 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

// I use open to get file descriptor then, use
// dup2 so that the stdin can point to the file given.

int redirect_input(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "no such file or directory", 25);
		ft_putstr_fd(filename, 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	return (fd);
}

// we will still need to close STDIN_FILENO;

// int main(void){
// 	void *buffer;
// 	int fd = redirect_input("infile");
// 	read(0, buffer, 20);
// 	printf("%s\n", (char *)buffer);

// 	close(fd);
// 	return (0);
// }