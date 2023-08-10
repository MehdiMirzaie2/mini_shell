#include "shell.h"

// check for errors
// split input
// check for redirections
// build the tree
// strtok

static unsigned int get_num_commands(char *input)
{
	unsigned int	i;

	i = 0;
	while (*input)
	{
		if (*input == ' ')
			i++;
		++input;
	}
	return (i);
}


int	process_input(char *input)
{
	t_cmdtree		cmdtree;
	unsigned int	num_commands;

	num_commands = get_num_commands(input);
}