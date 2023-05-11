/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 14:47:29 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/11 19:49:44 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	(*initialize_pipes(int n))[2]
{
	int (*pipe_fd)[2];
	int i;

	pipe_fd = malloc(n * sizeof(int[2]));
	i = 0;
	while (i < n)
	{
		pipe(pipe_fd[i]);
		i++;
	}
	return pipe_fd;
}

void	close_pipes(int n, int (*pipe_fd)[2])
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipe_fd[i][READ]);
		close(pipe_fd[i][WRITE]);
		i++;
	}
}

