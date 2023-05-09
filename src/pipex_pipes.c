/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_pipes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 14:47:29 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/09 14:48:09 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	(*initialize_pipes(int n))[2]
{
	int (*pipe_array)[2] = ft_malloc(n * sizeof(int[2]), "initialize_pipes");
	int i;

	i = 0;
	while (i < n)
	{
		pipe(pipe_array[i]);
		i++;
	}
	return pipe_array;
}

void	close_pipes(int n, int (*pipe_array)[2])
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipe_array[i][READ]);
		close(pipe_array[i][WRITE]);
		i++;
	}
}

