/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:26:51 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/12 16:35:27 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <string.h>

# include "libft.h"
# include "ast.h"
# include "builtins.h"
# include "utils.h"
# include "mysignal.h"

typedef struct s_vars	t_vars;
typedef struct s_shell	t_shell;
typedef struct s_fd		t_fd;

typedef struct s_mshctx	t_mshctx;

struct s_mshctx
{
	t_env	*env;
	t_ast	*ast;
	t_token	*lst;
	char	*line;
	char	*prompt;
};
/* free.c */
void free_mshctx(t_mshctx ctx);
int	free_strarr(char **array);

/* main.c */
char	*rl_gets(t_mshctx *msh);

/*
Deletes /tmp/mytempfileXXXXXX which was created for heredoc
*/
void		delete_tempfile(void);

/*
Adds a node to the neivornmefaat ars
*/
void		add_node_to_env(t_env **our_env, char *name, char *args);

/* env.c */
/* Creates a new environement variable list */
void		create_env(t_env *our_env, char **env);
void		free_env(t_env *env, bool all);

/* Return the value of an environement variable.
 * Returns NULL if environement variable doesn't exist.
 */
char		*env_get(t_env *our_env, char *name);

/* Sets or creates a new environment variabled named 'key'
 * to the value of 'value' (duplicated)
 */
void		env_set(t_env *our_env, char *key, char *value);

/* expand.c */

/* Expands env vars within the nodes and commands of an ast.
 */
void		ast_expandall(t_ast *ast, t_env *env);

/* Expands env vars within the name and args of a command.
 * USEDIN: ast_expandall.
 */
void		cmd_expand(t_cmd *cmd, t_env *env);

/* Returns a new string where env vars have been expanded.
 * Expanded string is a new string if the var was found.
 * otherwise it returns 'str'.
 * USEDIN: cmd_expand
 */
char		*expand_str(char *str, t_env *env);

/* expand_utils.c */
int			isenvstr(int c);
t_sd_stat	until_var_end(char *str, int i, bool mode, void *ctx);
t_sd_stat	until_var_or_quote(char *str, int i, bool mode, void *ctx);

/* expand_handle.c */
char		*handle_single(char *str, char **expand);
char		*handle_var(char *str, char **expand, t_env *env);
char		*handle_word(char *str, char quote, char **expand, t_env *env);
char		*handle_double(char *str, char quote, char **expand, t_env *env);

#endif
