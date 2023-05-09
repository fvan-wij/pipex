/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 18:33:47 by flip          #+#    #+#                 */
/*   Updated: 2023/05/09 17:24:05 by fvan-wij      ########   odam.nl         */
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

int	run_initial_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int	infile;

	print_cmds(cmd_node);
	infile = open(meta->infile, O_RDONLY);
	if (infile < 0)
		perror("error");
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO);
	close_pipes(meta->cmd_count - 1, pipe_fd);
	if (!execve(cmd_node->cmd_path, cmd_node->cmds, envp))
		perror("error");
	return (-1);
}

int	run_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{ 
	print_cmds(cmd_node);
	dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO); //pipe[0][READ]
	dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO); //pipe[1][WRITE]
	close_pipes(meta->cmd_count - 1, pipe_fd);
	if (!execve(cmd_node->cmd_path, cmd_node->cmds, envp))
		perror("error");
	return (-1);
}

int run_final_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int	outfile; print_cmds(cmd_node);
	dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO); //pipe[1][READ]
	outfile = open(meta->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		perror("error");
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close_pipes(meta->cmd_count - 1, pipe_fd);
	if (!execve(cmd_node->cmd_path, cmd_node->cmds, envp))
		perror("error");
	return (-1);
}

int	spawn_child_process(t_pipex *meta, int process_count, char *envp[], int (*pipe_fd)[])
{
	t_cmd	*cmd_node;
	int		error_code;

	error_code = -1;
	if (!find_cmd(meta->cmd_list, &cmd_node, process_count))
		return (perror("Error: could not match cmd_node with process_count!"), error_code);
	if (!cmd_node)
		return (perror("Could not find cmd in cmd_list"), 2);
	if (process_count == 0)
		error_code = run_initial_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	else if (process_count != 0 && process_count != meta->cmd_count -1)
		error_code = run_child_process(meta, cmd_node, pipe_fd, envp, process_count);		
	else 
		error_code = run_final_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	printf("error_code: %d\n", error_code);
	return (error_code);
}

