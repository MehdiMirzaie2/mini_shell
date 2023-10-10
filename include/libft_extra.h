/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:03:48 by clovell           #+#    #+#             */
/*   Updated: 2023/10/10 11:00:47 by mehdimirzai      ###   ########.fr       */
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
	E_SD_STOP = 4,
	E_SD_STOP_IM = 8,
};

/* String Duplicate Until
 * Creates a duplicated string from that start of 'src'
 * Until a character from 'until' is found.
 */
typedef t_sd_stat	(*t_strdupctxfn)(char*, int, bool, void*);

char	*ft_strdupu(char *src, char *until);
char	*ft_strdupct(char *src, int (*check)(int c));

/* Character-Conditional string copy and counter.
 * DESCRIPTION
 * Copies characters from `src` to `dst` based on the return result of `func`.
 * 
 * if `dst` is null, no copying will occurred.
 * use this to count the amount of characters the new string will.
 * (becareful on how context behaves when two passes, use func:check correctly.
 *
 * `func` is invoked per character of src.
 * args of func: `char* source, int index, bool check, void* context`
 * `func:src` is the same as `src`
 * `func:index` is the index of the current character
 * `func:check` the current pass of the duplication occurred SEE ft_strdupctx
 * `func:context` current context, stores a state for advanced conditioning
 *
 * RETURN VALUES
 * 	Returns the number of characters that would be copied into the new string 
 * 	-- excluding null-terminator.
 */
int		iter_strdupctx(char *src, char *dst, void *ctx, t_strdupctxfn func);

/* Character-Conditional string duplication
 * DESCRIPTION
 * Conditionally copies characters from source into a new string.
 * based on the return result of the supplied function `check`
 *
 * SEE ALSO
 * 	iter_strdupctx
 */
char	*ft_strdupctx(char *src, void *ctx, t_strdupctxfn check);
int		ft_isspace(int c);
int		ft_isalnum(int c);

#endif
