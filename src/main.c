/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/05/18 15:49:52 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

void	f()
{
	system("leaks pipex");
}

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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipes	*pipe_fd;
	t_pipex	*meta;
	pid_t	pid;
	int		status;

	atexit(f);
	pid = 1;
	if (argc < 5)
		return (-1);
	if (!init_data_struct(&meta, argc, argv))
		return (perror("pipex"), -2);
	parse_input(meta, argc, argv, envp);
	pipe_fd = initialize_pipes(meta->cmd_count - 1);
	if (!pipe_fd)
		free_pipex(meta, 1);
	if (execute_cmd(meta, envp, pipe_fd, &pid) == -1)
		free_pipex(meta, ERR_EXECUTION);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	free(pipe_fd);
	free_pipex(meta, WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}
