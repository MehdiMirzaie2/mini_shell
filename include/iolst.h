#ifndef IOLST_H
# define IOLST_H
# include <stdbool.h>
# include "lexer.h"

typedef struct s_iolst t_iolst;

struct s_iolst
{
	t_ttoken	type;
	char		*str;
	int			dup;
	// t_ttoken	type;s

	t_iolst		*next;
};

void iolst_memman(t_iolst **lst, bool destroy);
t_iolst *iolst_add(t_ttoken tok, char *str, int dup, t_iolst **head);
#endif
