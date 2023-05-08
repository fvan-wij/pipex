/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 18:33:47 by flip          #+#    #+#                 */
/*   Updated: 2023/05/08 10:43:43 by flip          ########   odam.nl         */
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

// int	run_initial_child_process(t_pipex *meta, t_cmd *cmd_node, int pipe_fd[], char *envp[])
// {
// 	int	error_code;
// 	int	infile;
//
// 	printf("--> cmd#%d [%s]\n", cmd_node->cmd_index, cmd_node->cmds[0]);
// 	close(pipe_fd[READ]);
// 	infile = open(meta->infile, O_RDONLY);
// 	dup2(infile, STDIN_FILENO);
// 	dup2(pipe_fd[WRITE], STDOUT_FILENO);
// 	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
// 	return (error_code);
// }
//
// int	run_child_process(t_cmd *cmd_node, int pipe_fd[], char *envp[])
// {
// 	int error_code;
// 	
// 	printf("--> cmd#%d [%s]\n", cmd_node->cmd_index, cmd_node->cmds[0]);
// 	dup2(pipe_fd[READ], STDIN_FILENO);
// 	dup2(pipe_fd[WRITE], STDOUT_FILENO);
// 	close(pipe_fd[READ]);
// 	close(pipe_fd[WRITE]);
// 	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
// 	return (error_code);
// }
//
// int run_final_child_process(t_pipex *meta, t_cmd *cmd_node, int pipe_fd[], char *envp[])
// {
// 	int error_code;
// 	int	outfile;
//
// 	printf("--> cmd#%d [%s]\n", cmd_node->cmd_index, cmd_node->cmds[0]);
// 	close(pipe_fd[WRITE]);
// 	dup2(pipe_fd[READ], STDIN_FILENO);
// 	outfile = open(meta->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	dup2(outfile, STDOUT_FILENO);
// 	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
// 	return (error_code);
// }

// int	spawn_child_process(t_pipex *meta, int process_count, char *envp[], int pipe_fd[])
// {
// 	t_cmd	*cmd_node;
// 	int		error_code;
//
// 	error_code = -1;
// 	if (!find_cmd(meta->cmd_list, &cmd_node, process_count))
// 		return (perror("Error: could not match cmd_node with process_count!"), error_code);
// 	if (!cmd_node)
// 		return (perror("Could not find cmd in cmd_list"), 2);
// 	if (process_count == 0)
// 		error_code = run_initial_child_process(meta, cmd_node, pipe_fd, envp);
// 	else if (process_count != 0 && process_count != meta->cmd_count -1)
// 		error_code = run_child_process(cmd_node, pipe_fd, envp);		
// 	else 
// 		error_code = run_final_child_process(meta, cmd_node, pipe_fd, envp);
// 	printf("error_code: %d\n", error_code);
// 	return (error_code);
// }

int	run_initial_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int	error_code;
	int	infile;

	printf("--> cmd#%d [%s]\n", cmd_node->cmd_index, cmd_node->cmds[0]);
	close(pipe_fd[process_count][READ]);
	// close(pipe_fd[process_count + 1][WRITE]);
	infile = open(meta->infile, O_RDONLY);
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO);
	// close(pipe_fd[process_count][WRITE]);
	// close(pipe_fd[process_count + 1][WRITE]);
	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (error_code);
}

int	run_child_process(t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int error_code;
	
	printf("--> cmd#%d [%s]\n", cmd_node->cmd_index, cmd_node->cmds[0]);
	close(pipe_fd[process_count][READ]);
	close(pipe_fd[process_count - 1][WRITE]);
	dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO);
	dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO);
	close(pipe_fd[process_count - 1][READ]);
	close(pipe_fd[process_count][WRITE]);
	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (error_code);
}

int run_final_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count)
{
	int error_code;
	int	outfile;

	printf("--> cmd#%d [%s]\n", cmd_node->cmd_index, cmd_node->cmds[0]);
	close(pipe_fd[process_count - 1][WRITE]);
	// close(pipe_fd[process_count][WRITE]);
	close(pipe_fd[process_count - 1][WRITE]);
	// close(pipe_fd[process_count][WRITE]);
	dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO);
	close(pipe_fd[process_count - 1][READ]);
	outfile = open(meta->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(outfile, STDOUT_FILENO);
	error_code = execve(cmd_node->cmd_path, cmd_node->cmds, envp);
	return (error_code);
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
		error_code = run_child_process(cmd_node, pipe_fd, envp, process_count);		
	else 
		error_code = run_final_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	printf("error_code: %d\n", error_code);
	return (error_code);
}

