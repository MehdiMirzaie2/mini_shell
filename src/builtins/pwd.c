/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:32:01 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/19 21:57:50 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>

void	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
		perror("getcwd() error");
	else
		ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
}
