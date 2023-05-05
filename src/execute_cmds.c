/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmds.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 23:55:30 by flip          #+#    #+#                 */
/*   Updated: 2023/05/05 17:50:10 by fvan-wij      ########   odam.nl         */
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

int	run_initial_child_process(t_cmd *cmd_node, int pipe_fd[], char *envp[])
{
	int	error_code;
	int	infile;

	printf("first cmd [%s]\n", cmd_node->cmds[0]);
	close(pipe_fd[0]);
	infile = open("infile", O_RDONLY);
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (error_code);
}

int	run_child_process(t_cmd *cmd_node, int pipe_fd[], char *envp[])
{
	int error_code;
	
	printf("middle cmd [%s]\n", cmd_node->cmds[0]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (error_code);
}

int run_final_child_process(t_cmd *cmd_node, int pipe_fd[], char *envp[])
{
	int error_code;
	int	outfile;

	printf("last cmd [%s]\n", cmd_node->cmds[0]);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(outfile, STDOUT_FILENO);
	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (error_code);
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

