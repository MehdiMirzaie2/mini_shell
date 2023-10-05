/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:31:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/05 14:19:48 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ast.h"
# include "cmd.h"

typedef struct s_env	t_env;

struct s_env
{
	char	*name;
	char	*args;
	t_env	*next;
};

int		ft_cd(t_cmd *cmd, t_env **our_env);
void	ft_env(t_env *our_env);
int		ft_export(t_env **our_env, t_arglst *args);
int		unset(t_env *our_env, t_arglst *args);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	exiting(int	*value, t_cmd *cmd);

#endif