/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_execution.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/11 11:35:23 by flip          ########   odam.nl         */
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

int	execute_cmd(t_pipex *meta, char *envp[])
{
	int		execution_status;
	pid_t	pid;
	int		(*pipe_array)[2];

	pid = 1;
	pipe_array = initialize_pipes(meta->cmd_count - 1);
	while (meta->process_count < meta->cmd_count - 1 && pid != 0)
	{
		meta->process_count++;
		pid = fork();
		if (pid == -1)
			perror("Error: forking has failed.\n");
		else if (pid == 0)
			execution_status = spawn_child_process(meta, meta->process_count, envp, pipe_array);
	}
	close_pipes(meta->cmd_count - 1, pipe_array);
	return (execution_status);
}

