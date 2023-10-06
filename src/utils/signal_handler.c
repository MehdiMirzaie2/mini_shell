/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:48:35 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/06 16:42:33 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "shell.h"

void	delete_tempfile(void)
{
	extern char	**environ;
	struct stat	buffer;
	int			fd;

	if (stat("/tmp/mytempfileXXXXXX", &buffer) == 0)
	{
		fd = open("/tmp/mytempfileXXXXXX", O_RDWR);
		if (fd < 0)
			perror("failed to open file\n");
		close(fd);
		if (unlink("/tmp/mytempfileXXXXXX") < 0)
			perror("could not unlink tmp/mytempfileXXXXXX\n");
	}
}

// void	handle_sigusr1(int sig)
// {
// 	if (sig == SIGUSR1)
// 	{
// 		delete_tempfile();
// 		exit(EXIT_SUCCESS);
// 	}
// }

void	handle_sigintheredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
}

void	handle_sigintexecute(int sig)
{
	(void)sig;
	return ;
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
