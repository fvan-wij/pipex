/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_execution.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/16 15:05:23 by fvan-wij      ########   odam.nl         */
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

int	execute_cmd(t_pipex *meta, char *envp[], int (*pipe_fd)[2], pid_t *pid)
{
	int		execution_status;

	while (meta->process_count < meta->cmd_count - 1 && *pid != 0)
	{
		meta->process_count++;
		*pid = fork();
		if (*pid == -1)
			free_va_mem_and_exit("%ll %2d %gm", meta->cmd_list, meta->bin_path, meta);
		else if (*pid == 0)
			execution_status = spawn_child_process(meta, meta->process_count, envp, pipe_fd);
	}
	close_pipes(meta->cmd_count - 1, pipe_fd);
	return (execution_status);
}

