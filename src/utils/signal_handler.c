/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:48:35 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/21 13:10:47 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// sigint should end the last process, then give prompt back
// sigquit should end minishell.
// i suggest use the global variable to determine what to do.


void handle_sigint(int sig)
{
    if (sig == SIGINT)
        g_value = SIGINT;
    else if (sig == SIGQUIT)
        g_value = SIGQUIT;
}
