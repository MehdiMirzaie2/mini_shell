/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:15:32 by clovell           #+#    #+#             */
/*   Updated: 2023/10/07 17:25:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libft_extra.h"

/* Creates a duplicated string from that start of 'src'
 * Until a character from 'until' is found.
 */
char	*ft_strdupu(char *src, char *until)
{
	int		i;
	char	*ret;

	if (src == NULL || until == NULL)
		return (NULL);
	i = 0;
	while (ft_strchr(until, src[i]) == NULL)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, src, i + 1);
	return (ret);
}

/*
 * Creates a duplicated string from that start of 'src'
 * Until a character satisfies he function 'check'.
 * check should be a function inside ctypes.h or similar:
 * 	eg:
 *		int isalnum(int c);
 *		int isalpha(int c);
 *		int iscntrl(int c);
 *		int isdigit(int c);
 *		int isgraph(int c);
 *		int islower(int c);
 *		int isprint(int c);
 *		int ispunct(int c);
 *		int isspace(int c);
 *		int isupper(int c);
 *		int isxdigit(int c);
 *		int isascii(int c);
 *		int isblank(int c);
 */
char	*ft_strdupct(char *src, int (*check)(int c))
{
	int		i;
	char	*ret;

	if (src == NULL)
		return (NULL);
	i = 0;
	while (src[i] && check(src[i]) == 0)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, src, i + 1);
	return (ret);
}

int	iter_strdupctx(char *src, char *ret, void *ctx, t_strdupctxfn func)
{
	t_sd_stat	state;
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (src[i])
	{
		state = func(src, i, ret != NULL, ctx);
		if (state & E_SD_COPY)
		{
			if (ret != NULL)
				ret[j] = src[i];
			j++;
		}
		if (state & E_SD_STOP)
			break ;
		i++;
	}
	if (ret != NULL && !(state & E_SD_STOP_IM))
		ret[j] = '\0';
	return (j);
}

// TODO: Info
char	*ft_strdupctx(char *src, void *ctx, t_strdupctxfn func)
{
	char	*ret;
	int		i;

	if (src == NULL)
		return (NULL);
	i = iter_strdupctx(src, NULL, ctx, func);
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	i = iter_strdupctx(src, ret, ctx, func);
	return (ret);
}
