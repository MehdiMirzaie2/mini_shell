#include <stdbool.h>

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token t_token;
typedef enum e_ttoken t_ttoken;

enum e_ttoken
{
	E_NA = 0,
	E_DQ = 1,
	E_SQ = 2,
	E_GS = E_DQ | E_SQ,
	E_LA = 4,
	E_RA = 8,
	E_LLA = 16,
	E_RRA = 32,
	E_WD = 64,
	E_P = 128,
	E_ALL = 256
};

/* Represents a fundamental unit of a/many command/s.
 *
 * type:	The type that this token represents, see e_ttoken.
 *
 * str:	The start of the string that is linked with this token.
 * 		if 'dup' is false this string may overlap other tokens.
 * 
 * dup:	true when str is a filtered copy of the input.
 * 		false when str is just the pointer inside the input.
 *
 * next:	The next token in the list.
 */
struct s_token
{
	t_ttoken	type;
	char		*str;
	bool		dup;

	t_token		*next;
};

char	*get_token_desc(t_ttoken t, int tostring);
void	*tlst_destroy(t_token *token);
t_token	*tlst_dup_pass(t_token *head);
t_token	*tlst_token_new(char *str, t_ttoken type, t_token *parent);
t_token	*tlst_create(char *str);
void	tlst_print(t_token *start);

int		ft_isspace(int c);

#endif
