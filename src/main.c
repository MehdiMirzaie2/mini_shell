#include "shell.h"

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

    /* If the line has any text in it, save it on the history. */
    if (*line_read && **line_read)
        add_history(*line_read);

    return *line_read;
    /* Read a string, and return a pointer to it.  Returns NULL on EOF. */
}


int main(void)
{
    /* A static variable for holding the line. */
    t_cmdtree               *cmdtree;
    static char *line_read  = NULL;

    cmdtree = NULL;
	while (1)
    {
        // printf("mini_shell ");

        rl_gets(&line_read); // Pass the pointer by reference
		process_input(line_read, cmdtree);
        // printf("%s\n", line_read);
        // Do something with line_read, if needed

        // Free the memory after you're done using it
        free_ast(cmdtree);
    }
	free(line_read);
    return (0);
}
