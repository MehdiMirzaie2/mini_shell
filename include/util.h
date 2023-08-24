#include <stdbool.h>
typedef struct s_strlst t_strlst;

struct s_strlst
{
	char		*str;
	bool		dup;
	t_strlst	*next;
};

void strlst_memman(t_strlst **lst, bool destroy);
t_strlst *strlst_add(char *str, int dup, t_strlst **head);

