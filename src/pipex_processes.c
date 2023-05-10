/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 18:33:47 by flip          #+#    #+#                 */
/*   Updated: 2023/05/10 16:03:43 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	run_initial_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int	infile;
	int status;
	// char *error_msg;

	status = 0;
	print_cmds(cmd_node);
	infile = open(meta->infile, O_RDONLY);
	if (infile < 0)
		perror("error");
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO);
	close_pipes(meta->cmd_count - 1, pipe_fd);
	status = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (status);
}

int	run_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int status;

	status = 0;
	print_cmds(cmd_node);
	dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO); //pipe[0][READ]
	dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO); //pipe[1][WRITE]
	close_pipes(meta->cmd_count - 1, pipe_fd);
	execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (-1);
}

int run_final_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int	outfile; 
	int status;
	
	status = 0;
	print_cmds(cmd_node);
	dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO); //pipe[1][READ]
	outfile = open(meta->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		perror("error");
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close_pipes(meta->cmd_count - 1, pipe_fd);
	if (execve(cmd_node->cmd_path, cmd_node->cmds, envp) == -1)
		perror("Error executing command");
	return (-1);
}

int	spawn_child_process(t_pipex *meta, int process_count, char *envp[], int (*pipe_fd)[])
{
	t_cmd	*cmd_node;
	int		status;

	status = -1;
	if (!find_cmd(meta->cmd_list, &cmd_node, process_count))
		return (perror("Error: could not match cmd_node with process_count!"), status);
	if (!cmd_node)
		return (perror("Could not find cmd in cmd_list"), 2);
	if (process_count == 0)
		status = run_initial_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	else if (process_count != 0 && process_count != meta->cmd_count -1)
		status = run_child_process(meta, cmd_node, pipe_fd, envp, process_count);		
	else 
		status = run_final_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	return (status);
}

