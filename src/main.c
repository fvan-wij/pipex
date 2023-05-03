/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/05/03 00:34:36 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

void	print_cmds(t_pipex **meta)
{
	int 	i;
	t_cmd	*current;

	current = (*meta)->cmd_list;
	while (current != NULL)
	{
		i = 0;
		while (current->cmds[i])
		{
			printf("Cmd[%i]: %s\n", i, current->cmds[i]);
			i++;
		}
		current = current->next;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipex *meta;
	int		pid;

	meta = malloc(sizeof(t_pipex) * 1);
	ft_bzero(meta, sizeof(t_pipex));
	if (argc == 5 && parse_input(meta, argv, envp))
		write(1, "PARSING_STATUS: Correct input.\n\n", 31);
	else
		write(1, "PARSING_STATUS: Incorrect argc.\n\n", 33);
	print_cmds(&meta);
	pid = fork();
	if (pid == 0)
	{
		execute_cmd(meta, 0, envp);
	}
	return (EXIT_SUCCESS);
}

