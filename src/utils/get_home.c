/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:59:49 by clovell           #+#    #+#             */
/*   Updated: 2023/10/17 11:38:16 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

/* SEE shell.h */
char	*get_home(t_env *env)
{
	if (env && env_get(env, "HOME"))
		return (env_get(env, "HOME"));
	else if (getenv("HOME"))
		return (getenv("HOME"));
	return (ft_strdup("/tmp/no_home"));
}
