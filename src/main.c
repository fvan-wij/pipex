/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/05/05 17:36:44 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

void	print_cmds(t_pipex **meta)
{
	int 	i;
	int		j;
	t_cmd	*current;

	current = (*meta)->cmd_list;
	j = 0;
	while (current != NULL)
	{
		i = 0;
		while (current->cmds[i])
		{
			printf("Cmd[%i][%i]: %s\n", j, i, current->cmds[i]);
			i++;
		}
		printf("\n");
		j++;
		current = current->next;
	}
}

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

int main(int argc, char *argv[], char *envp[])
{
	t_pipex *meta;
	pid_t	pid;
	int		(*pipe_array)[2];
	int		execution_status;

	meta = malloc(sizeof(t_pipex) * 1);
	ft_bzero(meta, sizeof(t_pipex));
	meta->process_count = -1;
	meta->cmd_count = 0;
	execution_status = 0;
	if (argc >= 5 && parse_input(meta, argc, argv, envp))
		write(1, "PARSING_STATUS: Correct input.\n\n", 31);
	else
	{
		write(1, "PARSING_STATUS: Incorrect argc.\n\n", 33);
		exit(1);
	}
	pipe_array = initialize_pipes(meta->cmd_count - 1);
	pid = 1;
	while (meta->process_count < meta->cmd_count - 1 && pid != 0)
	{
		meta->process_count++;
		pid = fork();
		if (pid == 0)
			execution_status = execute_cmd(meta, meta->process_count, envp, pipe_array[0]);
	}
	return (execution_status);
}

