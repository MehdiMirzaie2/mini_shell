/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:20:01 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/13 01:56:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "arglst.h"
# include "lexer.h"
# include "iolst.h"

typedef struct s_cmd	t_cmd;

struct s_cmd
{
	char		*cmd;
	t_arglst	*args;

	bool		has_pipe;
	bool		has_redirect;
	bool		has_heredoc;
	t_iolst		*redirects;
};

void	cmd_memman(t_cmd	**cmd, bool destroy);
int		cmd_build(t_cmd *cmd, t_token **token);

/* process_ast.c */
void	get_command_name(char **dst, t_cmd *cmd, bool movearg);

#endif
