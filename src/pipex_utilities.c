/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utilities.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 14:45:13 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/09 14:45:44 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_cmds(t_cmd *cmd_node)
{
	int	i;

	i = 1;
	printf("--> cmd#%d [%s ", cmd_node->cmd_index, cmd_node->cmds[0]);
	while (cmd_node->cmds[i])
	{
		printf("%s", cmd_node->cmds[i]);
		i++;
	}
	printf("]\n");
}

