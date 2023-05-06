/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/05/06 14:12:19 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	t_pipex *meta;
	int		execution_status;

	meta = malloc(sizeof(t_pipex) * 1);
	ft_bzero(meta, sizeof(t_pipex));
	meta->process_count = -1;
	meta->cmd_count = 0;
	execution_status = 0;
	if (argc < 5 || !parse_input(meta, argc, argv, envp))
		return(perror("PARSING_STATUS: Incorrect argc.\n\n"), 1);
	execution_status = execute_cmd(meta, envp);
	return (execution_status);
}

