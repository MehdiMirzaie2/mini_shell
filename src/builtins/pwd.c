/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:32:01 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/29 16:55:05 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>

// 4096 is the maximum chars a path can be;

void	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
		perror("getcwd() error");
    else
		ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
}
