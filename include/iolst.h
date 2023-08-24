#ifndef IOLST_H
# define IOLST_H
# include <stdbool.h>
typedef struct s_iolst t_iolst;

struct s_iolst
{
	char		*redir;
	char		*str;
	int			dup;

	t_iolst	*next;
};

void iolst_memman(t_iolst **lst, bool destroy);
t_iolst *iolst_add(char *redir, char *str, int dup, t_iolst **head);
#endif
