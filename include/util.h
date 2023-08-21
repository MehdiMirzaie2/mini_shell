#include <stdbool.h>
typedef struct s_strlst t_strlst;

struct s_strlst
{
	char		*string;
	bool		dup;
	t_strlst	*next;
};
