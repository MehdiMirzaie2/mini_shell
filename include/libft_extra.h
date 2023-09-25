/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:03:48 by clovell           #+#    #+#             */
/*   Updated: 2023/09/20 16:55:28 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
/* String Duplicate Until
 * Creates a duplicated string from that start of 'src'
 * Until a character from 'until' is found.
 */
typedef int	(*t_strdupctxfn)(char*, int, bool, void*);

char *ft_strdupu(char *src, char *until);
char *ft_strdupct(char *src, int (*check)(int c));
char *ft_strdupi(char *src, int (*check)(char *src, int index));
char *ft_strdupctx(char *src, void *ctx, t_strdupctxfn check);

int	ft_isspace(int c);
int	ft_isalnum(int c);
