/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:06:05 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/09/26 12:11:31 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>

void	init_termios(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag = t.c_lflag & ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	reset_termios(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag = t.c_lflag | ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
