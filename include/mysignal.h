/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysignal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:41:19 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/07 12:19:19 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSIGNAL_H
# define MYSIGNAL_H

void	handle_sigintheredoc(int sig);
void	handle_sigintexecute(int sig);
void	handle_sigint(int sig);
void	handle_siquitsystem(int sig);

#endif