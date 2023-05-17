/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 14:47:29 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/17 17:09:45 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_pipes	*initialize_pipes(int n)
{
	t_pipes	*pipe_fd;
	int		i;

	pipe_fd = malloc(n * sizeof(int [2]));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pipe(pipe_fd[i]);
		i++;
	}
	return (pipe_fd);
}

void	close_pipes(int n, t_pipes *pipe_fd)
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
