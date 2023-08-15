#ifndef LEXER_H
# define LEXER_H

typedef struct s_token t_token;
typedef enum e_ttoken t_ttoken;

enum e_ttoken
{
	E_DQ = 1,
	E_SQ = 2,
	E_GS = E_DQ | E_SQ,
	E_LA = 4,
	E_RA = 8,
	E_WD = 16,
	E_P = 32,
	E_ALL = 64
};

struct s_token
{
	t_ttoken type;
	char *str;
	t_token *next;
};

char *get_token_desc(t_ttoken t);
t_token *create_token(char *str, t_ttoken type, t_token *parent);
t_token *tokenise(char *str);
void print_tokenlst(t_token *start);
int ft_isspace(int c);


#endif
