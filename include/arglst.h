#ifndef ARGLST_H
# define ARGLST_H

#include <stdbool.h>
typedef struct s_arglst t_arglst;


struct s_arglst
{
	char		*str;
	bool		dup;
	bool		expand;
	t_arglst	*next;
};

void arglst_memman(t_arglst **lst, bool destroy);
t_arglst *arglst_add(char *str, int dup, t_arglst **head);

#endif
