/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 18:33:47 by flip          #+#    #+#                 */
/*   Updated: 2023/05/05 18:37:49 by flip          ########   odam.nl         */
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

int	spawn_child_processes(t_pipex *meta, char *envp[])
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
			execution_status = execute_cmd(meta, meta->process_count, envp, pipe_array[0]);
	}
	return (execution_status);
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
