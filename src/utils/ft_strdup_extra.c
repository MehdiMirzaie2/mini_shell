/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:15:32 by clovell           #+#    #+#             */
/*   Updated: 2023/10/02 17:12:55 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libft_extra.h"

/* Creates a duplicated string from that start of 'src'
 * Until a character from 'until' is found.
 */
char *ft_strdupu(char *src, char *until)
{
	int	i;
	char *ret;

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
 * */
char *ft_strdupct(char *src, int (*check)(int c))
{
	int	i;
	char *ret;

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

/* Creates a duplicated of 'src' where 'check' determins:
 * when the string should start.
 * when the string should end.
 * what characters to include.
 *
 * check return values:
 * 0 exclude char
 * 1 include char
 * 2 stop string
 *
 * check:
 *  should be deterministic.
 *  should stop string when encountering '\0'.
 */
char *ft_strdupi(char *src, int (*check)(char *src, int index))
{
	int	i;
	int	j;
	char *ret;
	int state;

	i = 0;
	if (src == NULL)
		return (NULL);
	while (src[i] && check(src, i) != 2)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	state = 0;
	while (src[i])
	{
		state = check(src, i);
		if (state == 2)
			break ;
		else if (state == 1)
			ret[j++] = src[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}


static int strdupctx_loop(char *str[2], void *ctx, bool check, t_strdupctxfn func)
{
	char *const src = str[0];
	char *const ret = str[1];
	t_sd_stat	state;
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (src[i])
	{
		state = func(src, i, check, ctx);
		if (state & E_SD_COPY)
		{
			if (!check)
				ret[j] = src[i];
			j++;	
		}
		if (state & E_SD_STOP)
			break ;
		i++;
	}
	return (j);
}

// TODO: Info
char *ft_strdupctx(char *src, void *ctx, t_strdupctxfn func)
{
	char	*ret;
	int		i;

	if (src == NULL)
		return (NULL);
	i = strdupctx_loop((char *[2]){src, NULL}, ctx, true, func);
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	i = strdupctx_loop((char *[2]){src, ret}, ctx, false, func);
	ret[i] = '\0';
	return (ret);
}
