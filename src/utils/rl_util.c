/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:58:08 by clovell           #+#    #+#             */
/*   Updated: 2023/10/17 13:05:48 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "shell.h"

static char	*rl_gets_specific(t_mshctx *msh)
{
	int	nfd;
	int	exit_code;

	if (env_get(msh->env, "MSH_NOECHO") && !isatty(0))
	{
		nfd = open("/dev/null", O_WRONLY);
		dup2(nfd, STDERR_FILENO);
		rl_outstream = stderr;
		msh->line = readline(NULL);
		close(nfd);
	}
	else
		msh->line = readline(msh->prompt);
	if (msh->line == NULL)
	{
		exit_code = EXIT_SUCCESS;
		if (env_get(msh->env, "?") != NULL)
			exit_code = ft_atoi(env_get(msh->env, "?"));
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		free_mshctx(*msh);
		delete_tempfile();
		exit(exit_code);
	}
	return (msh->line);
}

char	*rl_gets(t_mshctx *msh)
{
	char		buff[PATH_MAX];
	static char	*prev_path;
	char		*path;

	if (msh->prompt)
		free(msh->prompt);
	path = buff;
	if (!getcwd(buff, sizeof(buff)))
		path = prev_path;
	prev_path = path;
	msh->prompt = ft_strfmt("%s> ", path);
	if (msh->line)
		free(msh->line);
	msh->line = rl_gets_specific(msh);
	if (msh->line && *msh->line)
		add_history(msh->line);
	return (msh->line);
}
