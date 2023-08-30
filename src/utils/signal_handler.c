/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:48:35 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/30 12:38:39 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        (void)sig;
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
        g_value = SIGQUIT;
}
