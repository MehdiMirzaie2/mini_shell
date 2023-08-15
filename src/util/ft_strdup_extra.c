#include <stdlib.h>
#include "libft.h"

/* Creates a duplicated string from that start of 'src'
 * Until a character from 'until' is found.
 */
char *ft_strdupu(char *src, char *until)
{
	int	i;
	char *ret;

	if (src == NULL || until == NULL)
		return (NULL);
	i = 0;
	while (ft_strchr(until, src[i]) == NULL)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, src, i + 1);
	return (ret);
}

/* 
 * Creates a duplicated string from that start of 'src'
 * Until a character satisfies he function 'check'.
 * check should be a function inside ctypes.h or similar:
 * 	eg:
 *		int isalnum(int c);
 *		int isalpha(int c);
 *		int iscntrl(int c);
 *		int isdigit(int c);
 *		int isgraph(int c);
 *		int islower(int c);
 *		int isprint(int c);
 *		int ispunct(int c);
 *		int isspace(int c);
 *		int isupper(int c);
 *		int isxdigit(int c);
 *		int isascii(int c);
 *		int isblank(int c);
 * */
char *ft_strdupct(char *src, int (*check)(int c))
{
	int	i;
	char *ret;

	if (src == NULL)
		return (NULL);
	i = 0;
	while (check(src[i]) == 0)
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, src, i + 1);
	return (ret);
}
