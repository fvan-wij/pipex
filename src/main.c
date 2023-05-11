/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/05/11 21:00:46 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

int	init_data_struct(t_pipex **meta, int argc, char *argv[])
{
	*meta = malloc(sizeof(t_pipex));
	if (!*meta)
		return (0);
	ft_bzero(*meta, sizeof(t_pipex));
	(*meta)->process_count = -1;
	(*meta)->cmd_count = 0;
	(*meta)->infile = argv[1];
	(*meta)->outfile = argv[argc - 1];
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipex *meta;
	pid_t	pid;
	int		status;
	int		(*pipe_fd)[2];

	pid = 0;
	if (!init_data_struct(&meta, argc, argv))
		return (perror("malloc"), 1);
	if (argc < 5 || !parse_input(meta, argc, argv, envp))
		return (free_va_mem("%2d %ll %gm", meta->bin_path, meta->cmd_list, meta), 1);
	if(!(pipe_fd = initialize_pipes(meta->cmd_count - 1)))
		return (free_va_mem("%2d %ll %gm", meta->bin_path, meta->cmd_list, meta), 1);
	execute_cmd(meta, envp, pipe_fd);
	while (waitpid(pid, &status, 0) && WEXITSTATUS(status) > 0)
	{
		perror("error");
		free_va_mem_and_exit("%2d %ll %gm %pa", meta->bin_path, meta->cmd_list, meta, pipe_fd);
	}
	return (EXIT_SUCCESS);
}

