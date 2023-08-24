#include "shell.h"


// we need to take care of exit status
// other people use the global variable for this.


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
    *line_read = readline(ft_strfmt("%s>", get_env("PWD")));
    // this takes care of control d, needs to free mem.
    if (!(*line_read))
        exit(EXIT_SUCCESS);

    /* If the line has any text in it, save it on the history. */
    if (*line_read && **line_read)
        add_history(*line_read);

    return *line_read;
    /* Read a string, and return a pointer to it.  Returns NULL on EOF. */
}

int main(char **env)
{
    /* A static variable for holding the line. */
    t_cmdtree               *cmdtree;
    t_env                   *our_env;
    static char *line_read  = NULL;

    our_env = malloc(sizeof(t_cmd));
    cmdtree = NULL;

    create_env(our_env, env);
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigint);
	while (1)
    {
        // printf("mini_shell ");
        rl_gets(&line_read); // Pass the pointer by reference
        if (ft_strncmp("exit", line_read, 4) == 0)
            exit(EXIT_SUCCESS);
		process_input(line_read, cmdtree);
        // Do something with line_read, if needed
        // take care of the signals in this part.

        // Free the memory after you're done using it
        free_ast(cmdtree);
    }
	free(line_read);
    return (0);
}
