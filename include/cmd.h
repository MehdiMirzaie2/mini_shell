#ifndef CMD_H
# define CMD_H

#include "arglst.h"
#include "lexer.h"
#include "iolst.h"

typedef struct s_cmd t_cmd;

struct s_cmd
{
	char *cmd;
	t_arglst *args;

	bool	has_pipe;
	bool	has_redirect;
	t_iolst *redirects;
	t_iolst *heredoc;
	t_iolst *strin;
	t_iolst *strout;
	t_iolst *strapp;
};

void cmd_memman(t_cmd	**cmd, bool destroy);
void cmd_build(t_cmd *cmd, t_token **token);

#endif