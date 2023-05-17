/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_execution.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/17 18:07:37 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	find_cmd(t_cmd *cmd_list, t_cmd **node, int process_count)
{
	*node = cmd_list;
	while (node != NULL)
	{
		if ((*node)->cmd_index == process_count)
			return (1);
		*node = (*node)->next;
	}
	return (0);
}

int	execute_cmd(t_pipex *meta, char *envp[], t_pipes *pipe_fd, pid_t *pid)
{
	int		execution_status;
	
	execution_status = 0;
	while (meta->process_count < meta->cmd_count - 1 && *pid != 0)
	{
		meta->process_count++;
		*pid = fork();
		if (*pid == -1)
			free_pipex(meta, -1);
		else if (*pid == 0)
			execution_status = spawn_child_process(meta, meta->process_count,
					envp, pipe_fd);
	}
	close_pipes(meta->cmd_count - 1, pipe_fd);
	return (execution_status);
}
