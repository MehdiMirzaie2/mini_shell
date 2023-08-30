/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:33:50 by clovell           #+#    #+#             */
/*   Updated: 2023/08/30 12:59:44 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "error.h"
#include "libft.h"

char	*errormsg(t_errormsg error)
{
	char *const	names[] = { 
	[E_MSG_ASTB_MALLOC] = "Failed to allocate ast builder, out of memory.",
	[E_MSG_AST_MALLOC] = "Failed to allocate ast node, out of memory.",
	[E_MSG_CMD_MALLOC] = "Failed to allocate command, out of memory.",
	[E_MSG_ARGLST_MALLOC] = "Failed to allocate arg list, out of memory.",
	[E_MSG_IOLST_MALLOC] = "Failed to allocate io list, out of memory.",
	[E_MSG_STRDUP_MALLOC] = "Failed to duplicate string, out of memory",
	};

	return (names[error]);
}

char	*errorname(t_error error)
{
	char *const	names[] = { 
	[E_MALLOCFAIL] = "MALLOC_FAIL"
	};

	return (names[error]);
}

void	ft_errx(t_error error, t_errormsg msg, char *file, int line)
{
	char *const	name = errorname(error);

	ft_putstr_fd("Error [", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("] ", STDERR_FILENO);
	ft_putstr_fd(errormsg(msg), STDERR_FILENO);
	ft_putstr_fd("\nOccurred at ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(-error + -(msg >> 4));
}
