/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:14:31 by clovell           #+#    #+#             */
/*   Updated: 2023/10/17 12:15:44 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

int	is_directory_exists(const char *path)
{
	struct stat	stats;

	stats = (struct stat){0};
	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}
