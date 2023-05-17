/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_redirection.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:54:10 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/17 15:42:25 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	redirect_init_child(int infile, int (*pipe_fd)[2],
		t_pipex *meta, int process_count)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO) == -1)
		return (-1);
	close(infile);
	close_pipes(meta->cmd_count - 1, pipe_fd);
	return (1);
}

int	redirect_child(int (*pipe_fd)[2], t_pipex *meta, int process_count)
{
	if (dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO) == -1)
		return (-1);
	if (dup2(pipe_fd[process_count][WRITE], STDOUT_FILENO) == -1)
		return (-1);
	close_pipes(meta->cmd_count - 1, pipe_fd);
	return (1);
}

int	redirect_final_child(int outfile, int (*pipe_fd)[2],
		t_pipex *meta, int process_count)
{
	if (dup2(pipe_fd[process_count - 1][READ], STDIN_FILENO) == -1)
		return (-1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (-1);
	close(outfile);
	close_pipes(meta->cmd_count - 1, pipe_fd);
	return (1);
}
