/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:31:36 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/09/20 13:36:15 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ast.h"
# include "cmd.h"

typedef struct s_env			t_env;

struct s_env
{
	char	*name;
	char	*args;
	t_env	*next;
};

void	ft_cd(char *path, t_env **our_env);
void	ft_env(t_env *our_env);
void	ft_export(t_env **our_env, char *args);
void	ft_echo(t_arglst *args, char *filename);
void	unset(t_env *our_env, char *name);
void	ft_pwd(void);
void	exiting(int	*value, t_cmd *cmd);
void	put_exitstatus(int value);

#endif