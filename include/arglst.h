/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:17:44 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/05 14:19:00 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGLST_H
# define ARGLST_H

# include <stdbool.h>

typedef struct s_arglst	t_arglst;

struct s_arglst
{
	char		*str;
	bool		dup;
	bool		expand;
	t_arglst	*next;
};

void		arglst_memman(t_arglst **lst, bool destroy);
t_arglst	*arglst_add(char *str, int dup, t_arglst **head);

#endif