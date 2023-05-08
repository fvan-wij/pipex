/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/05/08 23:03:58 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <string.h>
#include <stdio.h>


int	init_data_struct(t_pipex **meta, int argc, char *argv[])
{
	*meta = ft_malloc(sizeof(t_pipex), "init_data_struct");
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
	int		execution_status;

	execution_status = 0;
	if (!init_data_struct(&meta, argc, argv))
		return (perror("ALLOCATION_ERROR: error allocationg data for t_pipex *meta."), 1);
	if (argc < 5 || !parse_input(meta, argc, argv, envp))
		return(perror("PARSING_STATUS: Incorrect argc.\n\n"), 1);
	execution_status = execute_cmd(meta, envp);
	//TO DO: Wait for children to finish and then free memory accordingly.
	display_memory_usage();
	// atexit(leaks_pipex);
	return (execution_status);
}

