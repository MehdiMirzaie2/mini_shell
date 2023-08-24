#include "shell.h"
// #include "libft.h"

// check for errors
// split input
// check for redirections
// build the tree
// strtok


// process is the where we split the input and create the command tree;

// static unsigned int get_num_commands(char *input)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (*input)
// 	{
// 		if (*input == ' ')
// 			i++;
// 		++input;
// 	}
// 	return (i);
// }

static void	add_node_to_cmd(t_cmd *current, char *command, unsigned int flag)
{
	t_cmd	*reference;

	reference = current;
	if (flag == 1)
	{
		reference->arg = command;
		reference->next = NULL;
		return ;
	}
	reference->next = malloc(sizeof(t_cmd));
	if (!reference->next)
		return ;
	reference = reference->next;
	reference->arg = command;
	reference->next = NULL;
}

// static void add_node_to_cmdtree()
// {
// 	...;
// }

int	process_input(char *input, t_cmdtree *cmdtree)
{
	// unsigned int	num_commands;
	char			**splitted_input;
	t_cmd			*reference = NULL;
	t_cmdtree		*reference_cmdtree;
	unsigned int	flag;

	flag = 1;
	splitted_input = ft_split(input, ' ');
	cmdtree = malloc(sizeof(t_cmdtree));
	if (!cmdtree)
		return (0);
	reference_cmdtree = cmdtree;
	reference_cmdtree->next = NULL;
	reference = cmdtree->cmd;
	reference = malloc(sizeof(t_cmd));
	if (!reference)
		return (0);
	while (*splitted_input != NULL)
	{
		while (*splitted_input != NULL && *splitted_input[0] != '|' && *splitted_input[0] != '>'
			&& *splitted_input[0] != '<' && *splitted_input[0] != '&')
		{
			add_node_to_cmd(reference, *splitted_input, flag);
			if (!flag)
				reference = reference->next;
			flag = 0;
			++splitted_input;
		}
		if (*splitted_input[0] == '|' && *splitted_input[0] == '<'
			&& *splitted_input[0] == '>' && *splitted_input[0] == '&')
		{
			reference_cmdtree->redirect = *splitted_input;
			++splitted_input;
			reference_cmdtree->next = malloc(sizeof(t_cmdtree));
			reference_cmdtree = reference_cmdtree->next;
			reference_cmdtree->next = NULL;
		}
		else
			reference_cmdtree->redirect = NULL;
		flag = 1;
	}
	return (1);
}