/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/05/19 14:26:15 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	init_data_struct(t_pipex **meta, int argc, char *argv[], char **envp)
{
	*meta = malloc(sizeof(t_pipex));
	if (!*meta)
		return (0);
	ft_bzero(*meta, sizeof(t_pipex));
	(*meta)->process_count = -1;
	(*meta)->cmd_count = 0;
	(*meta)->infile = argv[1];
	(*meta)->outfile = argv[argc - 1];
	(*meta)->envp = envp;
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipes	*pipe_fd;
	t_pipex	*meta;
	pid_t	pid;
	int		status;

	pid = 1;
	if (argc < 5)
		return (ERR_ARGC_COUNT);
	if (!init_data_struct(&meta, argc, argv, envp))
		return (perror("pipex"), ERR_ALLOCATION);
	parse_input(meta, argc, argv);
	pipe_fd = initialize_pipes(meta->cmd_count - 1);
	if (!pipe_fd)
		exit_pipex(meta, ERR_ALLOCATION);
	if (execute_cmd(meta, pipe_fd, &pid) == -1)
		exit_pipex(meta, ERR_FORK);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	free(pipe_fd);
	exit_pipex(meta, WEXITSTATUS(status));
}
