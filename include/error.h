/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:14:16 by clovell           #+#    #+#             */
/*   Updated: 2023/10/17 12:00:50 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error	t_error;

enum e_error
{
	E_ERR_NOERR = 0,
	E_ERR_MALLOCFAIL,
	E_ERR_BADPARAM,
	E_ERR_NULLPARAM,
	E_ERR_STRDUP,
	E_ERR_NOFILE,
};

char	*errormsg(t_error error);
void	ft_errx(t_error a, char *file, int line);
void	ft_assert(int cond, t_error error, char *file, int line);

#endif
