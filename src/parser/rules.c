/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:37:33 by clovell           #+#    #+#             */
/*   Updated: 2023/10/13 10:38:58 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"

typedef enum e_syn_err_no	t_synerrno;
typedef struct s_synerror	t_synerror;

enum e_syn_err_no
{
	E_SEALLOWED,
	E_SEUNEXPECTED,
};

struct s_synerror
{
	t_token		*token;
	t_synerrno	error;
};

static int	print_synerr(t_ttoken token, t_token *lst, t_synerrno error)
{
	char	*fmt;
	char	*str;

	if (error == E_SEALLOWED)
		return (0);
	str = get_token_desc(token, 2);
	if (lst && lst->str)
		str = lst->str;
	fmt = "Unknown error";
	if (error == E_SEUNEXPECTED)
		fmt = "msh: syntax error near unexpected token `%s'\n";
	ft_printf_fd(STDERR_FILENO, fmt, str);
	return (1);
}

int	tlst_syntax_check(t_token *lst)
{
	t_token		*tcurr;
	t_ttoken	curr;
	t_ttoken	prev;
	t_ttoken	next;

	prev = E_TTNA;
	tcurr = lst;
	while (tcurr)
	{
		curr = tcurr->type;
		next = E_TTNA;
		if (tcurr->next)
			next = tcurr->next->type;
		if (prev == E_TTNA && (curr & E_TTNCP))
			return (print_synerr(curr, tcurr, E_SEUNEXPECTED));
		if (curr & E_TTLR && next != E_TTWD)
			return (print_synerr(next, NULL, E_SEUNEXPECTED));
		prev = curr;
		tcurr = tcurr->next;
	}
	return (0);
}
