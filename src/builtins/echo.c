/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:06:15 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/19 14:19:18 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*join_args(t_arglst *args)
{
	// int		num_args;
	char	*args_joined;
	bool	has_flag;

	args_joined = NULL;
	has_flag = false;
	if (!ft_strncmp(args->str, "-n", 2))
	{
		has_flag = true;
		args = args->next;
	}
	args_joined = args->str;
	args = args->next;
	while (args)
	{
		// args_joined = ft_strjoin(args_joined, args->str);
		args_joined = ft_strjoin(strcat(args_joined, " "), args->str);
		args = args->next;
	}
	if (!has_flag)
		args_joined = ft_strjoin(args_joined, "\n");
	return (args_joined);
}

void	ft_echo(t_arglst *args, char *filename)
{
	t_fd	fds;
	// int		option;
	char *args_joined;

	args_joined = join_args(args);
	if (filename == NULL)
	{
		(void)filename;
		(void)fds;
		ft_putstr_fd(args_joined, 1);
	}
	else
	{
		fds = redirect_output(filename);
		ft_putstr_fd(args_joined, fds.temp_out_in_fd);
		dup2(fds.saved_out_in_fd, STDOUT_FILENO);
		close(fds.saved_out_in_fd);
	}
}
