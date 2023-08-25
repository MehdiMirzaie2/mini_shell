/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:14:16 by clovell           #+#    #+#             */
/*   Updated: 2023/08/23 21:30:55 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error t_error;
typedef enum e_errormsg t_errormsg;

enum e_errormsg
{
	E_MSG_ASTB_MALLOC,
	E_MSG_AST_MALLOC,
	E_MSG_CMD_MALLOC,
	E_MSG_STRLST_MALLOC,
	E_MSG_STRDUP_MALLOC,
	E_MSG_IOLST_MALLOC
};

enum e_error
{
	E_MALLOCFAIL
};

char *errormsg(t_errormsg error);

char *errorname(t_error error);
void ft_errx(t_error error, t_errormsg, char *file, int line);
#endif
