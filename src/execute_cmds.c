/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmds.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/04 18:23:27 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	execute_cmd(t_pipex *meta, int process_count, char *envp[], int pipe_fd[])
{
	t_cmd	*node;
	int		error_code;
	int		i;
	int		file;

	i = 0;
	error_code = 0;
	node = meta->cmd_list;
	while (node->cmd_index != process_count && node->next != NULL)
		node = node->next;
	if (node->cmd_index != process_count)
		return (perror("Process couldn't match cmd_id."), 0);
	if (process_count == 0)
	{
		printf("first cmd [%s]\n", node->cmds[0]);
		close(pipe_fd[0]);
		file = open("infile", O_RDONLY);
		dup2(file, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		error_code = execve(node->cmd_path, node->cmds, envp);
	}
	else if (process_count == meta->cmd_count - 1)
	{
		printf("last cmd [%s]\n", node->cmds[0]);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		file = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(file, STDOUT_FILENO);
		error_code = execve(node->cmd_path, node->cmds, envp);
	}
	//To do: Implement pipes for commands that aren't the first or the last.
	printf("error_code: %d\n", error_code);
	return (error_code);
}

