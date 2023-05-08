/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_execution.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/08 22:52:55 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	(*initialize_pipes(int n))[2]
{
	int (*pipe_array)[2] = malloc(n * sizeof(int[2]));
	int i;

	i = 0;
	while (i < n)
	{
		pipe(pipe_array[i]);
		i++;
	}
	return pipe_array;
}

void	close_pipes(int n, int (*pipe_array)[2])
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipe_array[i][READ]);
		close(pipe_array[i][WRITE]);
		i++;
	}
}

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
		if (pid == 0)
			execution_status = spawn_child_process(meta, meta->process_count, envp, pipe_array);
	}
	close_pipes(meta->cmd_count - 1, pipe_array);
	return (execution_status);
}



