#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "lexer.h"

char *rl_gets(char **line_read)
{
    /* If the buffer has already been allocated, return the memory
        to the free pool. */
    if (*line_read)
    {
        free(*line_read);
        *line_read = NULL;
    }

    /* Get a line from the user. */
    *line_read = readline("mini_shell ");

	/* TODO: Handle quote modes */

	/* If the line has any text in it, save it on the history. */
    if (*line_read && **line_read)
        add_history(*line_read);

    return *line_read;
    /* Read a string, and return a pointer to it.  Returns NULL on EOF. */
}

void print_tokenlst(t_token *start);
int main(void)
{
	/* A static variable for holding the line. */
	static char *line_read = NULL;
	while (1)
	{
		// printf("mini_shell ");
		rl_gets(&line_read); // Pass the pointer by reference
		if (line_read[0] == '#') // For testing purposes
			line_read = ft_strdup("   \techo \t\"test \'(quote)\'\" \'sq\' <less | tr -r | awk '{printf $0}' | (first (second) (third (forth)))");
		tlst_print(tlst_create(line_read));
		printf("%s\n", line_read);
		// Do something with line_read, if needed
		// Free the memory after you're done using it
	}
	free(line_read);
	return (0);
}
