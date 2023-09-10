/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:14:16 by clovell           #+#    #+#             */
/*   Updated: 2023/09/10 20:05:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error t_error;

enum e_error
{
	E_ERR_NOERR = 0,
	E_ERR_MALLOCFAIL,
	E_ERR_BADPARAM,
	E_ERR_NULLPARAM,
	E_ERR_STRDUP,
};

char *errormsg(t_error error);

void ft_errx(t_error, char *file, int line);
void ft_assert(int cond, t_error error, char *file, int line);
#endif
