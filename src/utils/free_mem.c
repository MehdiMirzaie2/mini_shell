/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:57:01 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/14 12:06:03 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_ast(t_cmdtree *cmdtree)
{
	t_cmdtree	*reference_cmdtree;
	t_cmd		*reference_cmd;

	while (cmdtree->next != NULL)
	{
		reference_cmdtree = cmdtree;
		cmdtree = cmdtree->next;
		while (reference_cmdtree->cmd->next)
		{
			reference_cmd = reference_cmdtree->cmd;
			reference_cmdtree->cmd = reference_cmd->next;
			free(reference_cmd);
		}
		free(reference_cmdtree);
	}
}