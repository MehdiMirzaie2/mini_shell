/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:48:35 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/03 15:44:37 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
// #include <readline/readline.h>
#include "shell.h"

void    delete_tempfile(void)
{
    extern char **environ;
    struct stat buffer;
    int fd;

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

void handle_sigint(int sig)
{
    static bool reseved_sig = false;

    if (reseved_sig == false)
    {
        reseved_sig = true;
        if (sig == SIGINT)
        {
            g_value = SIGINT;
            kill(0, SIGUSR1);
            wait(NULL);
            dup2(STDIN_FILENO, IN);
            write(2, "\n", 1);
            // rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
        }
        else if (sig == SIGUSR1)
        {
            reseved_sig = false;
            delete_tempfile();
            exit(130);
        }
    }
    if (sig == SIGQUIT)
        return ;
}
