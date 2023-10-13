/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:22:01 by clovell           #+#    #+#             */
/*   Updated: 2023/10/13 10:44:52 by clovell          ###   ########.fr       */
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
		free(ptr->cmd);
		arglst_memman(&ptr->args, true);
		iolst_memman(&ptr->redirects, true);
		free(*cmd);
	}
}

static int	cmd_redir(t_cmd *cmd, t_token **adv)
{
	const t_token	tok = (**adv);

	if ((tok.type & E_TTLR) == 0)
		return (0);
	if (tok.next != NULL && (tok.next->type & E_TTWG) != 0)
	{
		iolst_add(tok.type, tok.next->str, 1, &cmd->redirects);
		*adv = (*adv)->next->next;
		cmd->has_redirect = true;
		cmd->has_heredoc = (tok.type & E_TTLLA) != 0;
		return (0);
	}
	if (tok.next == NULL)
		ft_putstr_fd("msh: syntax error near `newline`\n", 2);
	else
		ft_printf_fd(STDERR_FILENO,
			"msh: syntax error near `%s`\n", tok.next->str);
	return (1);
}

// static void	cmd_redir(t_cmd *cmd, t_token **adv)
// {
// 	const t_token	tok = (**adv);
// 	t_iolst **const	targets[] = {
// 	[E_TTLA] = &cmd->strin,
// 	[E_TTRA] = &cmd->strout,
// 	[E_TTRRA] = &cmd->strapp,
// 	[E_TTLLA] = &cmd->heredoc
// 	};

// 	cmd->has_redirect = true;
// 	if ((tok.type & E_TTLR) == 0)
// 		return ;
// 	if (tok.next != NULL && (tok.next->type & E_TTWG) != 0)
// 	{
// 		iolst_add(tok.type, tok.next->str, 1, targets[tok.type]);
// 		*adv = (*adv)->next->next;
// 		return ;
// 	}
// // 	//printf("missing or unexpected token");
// // 	//logmsg("unexpected token"); // handle more info
// // }

static int	cmd_start(t_cmd *cmd, t_token **adv)
{
	const t_token	tk = (**adv);

	if ((tk.type & E_TTWG) == 0)
	{
		if (cmd_redir(cmd, adv))
			return (1);
	}
	else
	{
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strdup(tk.str);
		else
			arglst_add(tk.str, 1, &cmd->args)->expand = (tk.type & E_TTSQ) == 0;
		*adv = tk.next;
	}
	return (0);
}

int	cmd_build(t_cmd *cmd, t_token **tokenadv)
{
	t_ttoken	token;

	token = (*tokenadv)->type;
	while ((token & E_TTNC) == 0)
	{
		if (cmd_start(cmd, tokenadv))
			return (1);
		if (*tokenadv == NULL)
			break ;
		token = (*tokenadv)->type;
	}
	return (0);
}
