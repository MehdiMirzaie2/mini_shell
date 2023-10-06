/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysignal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:41:19 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/06 16:42:49 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSIGNAL_H
# define MYSIGNAL_H

void	handle_sigintheredoc(int sig);
void	handle_sigintexecute(int sig);
void	handle_sigint(int sig);

#endif