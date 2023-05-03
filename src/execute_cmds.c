/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmds.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/03 00:47:37 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	execute_cmd(t_pipex *meta, int cmd_id, char *envp[])
{
	t_cmd	*node;
	int		error_code;
	int		i;

	i = 0;
	error_code = 0;
	node = meta->cmd_list;
	while (node->cmd_index != cmd_id && node->next != NULL)
		node = node->next;
	printf("node->cmd_index %d\nnode->cmd_path %s\n", node->cmd_index, node->cmd_path);
	if (node->cmd_index != cmd_id)
		return (perror("Process couldn't match cmd_id."), 0);
	while (meta->bin_path[i])
	{
		// printf("cmd_path: %s\n", node->cmd_path);
		if (access(node->cmd_path, X_OK) == 0)
		{
			error_code = execve(node->cmd_path, node->cmds, envp);
			printf("error_code: %d\n", error_code);
		}
		i++;
	}
	return (error_code);
}
