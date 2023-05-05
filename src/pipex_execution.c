/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_execution.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/05 18:35:34 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	*find_cmd(t_cmd *cmd_list, t_cmd **node, int process_count)
{
	*node = cmd_list;
	while (node != NULL)
	{
		if ((*node)->cmd_index == process_count)
		{
			printf("node->cmd_index: %d\tprocess_count: %d\n", (*node)->cmd_index, process_count);
			return (node);
		}
		*node = (*node)->next;
	}
	return (perror("Process couldn't match cmd_id"), NULL);
}


int	execute_cmd(t_pipex *meta, int process_count, char *envp[], int pipe_fd[])
{
	t_cmd	*cmd_node;
	int		error_code;

	error_code = -1;
	if (!find_cmd(meta->cmd_list, &cmd_node, process_count))
		return (error_code);
	if (!cmd_node)
		return (perror("Could not find cmd in cmd_list"), 2);
	if (process_count == 0)
		error_code = run_initial_child_process(cmd_node, pipe_fd, envp);
	else if (process_count != 0 && process_count != meta->cmd_count -1)
		error_code = run_child_process(cmd_node, pipe_fd, envp);		
	else 
		error_code = run_final_child_process(cmd_node, pipe_fd, envp);
	printf("error_code: %d\n", error_code);
	return (error_code);
}

