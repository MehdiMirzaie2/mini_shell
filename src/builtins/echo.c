/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:06:15 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/05 14:05:34 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*join_args(t_arglst *args)
{
	char	*args_joined;
	bool	has_flag;

	args_joined = NULL;
	has_flag = false;
	if (!args)
		return ("\n");
	while (args)
	{
		if (!ft_strncmp(args->str, "-n", 2))
			has_flag = true;
		else
		{
			if (args_joined == NULL)
				args_joined = args->str;
			else
				args_joined = ft_strjoin(strcat(args_joined, " "), args->str);
		}
		args = args->next;
	}
	if (!has_flag)
		args_joined = ft_strjoin(args_joined, "\n");
	return (args_joined);
}

void	ft_echo(t_cmd *cmd)
{
	char	*args_joined;

	args_joined = join_args(cmd->args);
	if (args_joined == NULL)
		return ;
	printf("%s", args_joined);
}
