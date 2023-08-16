/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:57:01 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/08/16 16:13:35 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_ast(t_cmdtree *cmdtree)
{
	t_cmdtree	*reference_cmdtree;
	t_cmd		*reference_cmd;

	if (cmdtree->next == NULL){
		reference_cmdtree = cmdtree;
		cmdtree = cmdtree->next;
		while (reference_cmdtree->cmd != NULL)
		{
			reference_cmd = reference_cmdtree->cmd;
			reference_cmdtree->cmd = reference_cmd->next;
			free(reference_cmd);
		}
	}
	else{
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
}