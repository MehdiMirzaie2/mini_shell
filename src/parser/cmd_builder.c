/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:22:01 by clovell           #+#    #+#             */
/*   Updated: 2023/09/20 14:57:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "standard.h"
#include "cmd.h"
#include "lexer.h"

void	cmd_memman(t_cmd **cmd, bool destroy)
{
	t_cmd *const	ptr = (*cmd);
	const t_cmd		builder = {0};

	if (!destroy)
	{
		(*cmd) = malloc(sizeof(t_cmd));
		ft_assert(*cmd == NULL, E_ERR_MALLOCFAIL, __FILE__, __LINE__);
		**cmd = builder;
	}
	else
	{
		if (*cmd == NULL)
			return ;
		arglst_memman(&ptr->args, true);
		iolst_memman(&ptr->heredoc, true);
		iolst_memman(&ptr->strapp, true);
		iolst_memman(&ptr->strin, true);
		iolst_memman(&ptr->strout, true);
	}
}

static void	cmd_redir(t_cmd *cmd, t_token **adv)
{
	const t_token	tok = (**adv);
	t_iolst **const	targets[] = {
	[E_TTLA] = &cmd->strin,
	[E_TTRA] = &cmd->strout,
	[E_TTRRA] = &cmd->strapp,
	[E_TTLLA] = &cmd->heredoc
	};

	cmd->has_redirect = true;
	if ((tok.type & E_TTLR) == 0)
		return ;
	if (tok.next != NULL && (tok.next->type & E_TTWG) != 0)
	{
		iolst_add(tok.type, tok.next->str, 1, targets[tok.type]);
		*adv = (*adv)->next->next;
		return ;
	}
	//printf("missing or unexpected token");
	//logmsg("unexpected token"); // handle more info
}

static void	cmd_start(t_cmd *cmd, t_token **adv)
{
	const t_token	tk = (**adv);

	if ((tk.type & E_TTWG) == 0)
		cmd_redir(cmd, adv);
	else
	{
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strdup(tk.str);
		else
			arglst_add(tk.str, 1, &cmd->args)->expand = (tk.type & E_TTSQ) == 0;
		*adv = tk.next;
	}
}

void	cmd_build(t_cmd *cmd, t_token **tokenadv)
{
	t_ttoken	token;

	token = (*tokenadv)->type;
	while ((token & E_TTNC) == 0)
	{
		cmd_start(cmd, tokenadv);
		if (*tokenadv == NULL)
			break ;
		token = (*tokenadv)->type;
	}
}
