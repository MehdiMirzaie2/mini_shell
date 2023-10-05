/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iolst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:22:58 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/05 14:23:01 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOLST_H
# define IOLST_H

# include <stdbool.h>
# include "lexer.h"

typedef struct s_iolst	t_iolst;

struct s_iolst
{
	t_ttoken	type;
	char		*str;
	int			dup;
	t_iolst		*next;
};

void	iolst_memman(t_iolst **lst, bool destroy);
t_iolst	*iolst_add(t_ttoken tok, char *str, int dup, t_iolst **head);

#endif