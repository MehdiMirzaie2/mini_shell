/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:03:48 by clovell           #+#    #+#             */
/*   Updated: 2023/10/05 14:26:20 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EXTRA_H
# define LIBFT_EXTRA_H

# include "libft.h"
# include <stdbool.h>

typedef enum e_sd_stat	t_sd_stat;

enum	e_sd_stat
{
	E_SD_SKIP = 0,
	E_SD_COPY = 1,
	E_SD_STOP = 4
};

/* String Duplicate Until
 * Creates a duplicated string from that start of 'src'
 * Until a character from 'until' is found.
 */
typedef t_sd_stat	(*t_strdupctxfn)(char*, int, bool, void*);

char	*ft_strdupu(char *src, char *until);
char	*ft_strdupct(char *src, int (*check)(int c));
char	*ft_strdupi(char *src, int (*check)(char *src, int index));
char	*ft_strdupctx(char *src, void *ctx, t_strdupctxfn check);
int		ft_isspace(int c);
int		ft_isalnum(int c);

#endif
