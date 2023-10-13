/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:06:15 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/13 13:01:09 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_echo(t_cmd *cmd)
{
	t_arglst	*args;
	int			println;

	println = 1;
	args = cmd->args;
	if (args == NULL)
		println = 1;
	while (args && ft_strncmp("-n", args->str, 3) == 0)
	{
		println = 0;
		args = args->next;
	}
	while (args)
	{
		printf("%s", args->str);
		args = args->next;
		if (args)
			printf(" ");
	}
	if (println)
		printf("\n");
}
