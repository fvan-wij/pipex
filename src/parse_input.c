/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 15:06:41 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/01 17:40:37 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	is_infile(char *infile)
{
	int fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}

int is_outfile(char *outfile)
{
	int fd;

	fd = open(outfile, O_CREAT, O_RDWR);
	if (fd < 0)
		return (0);
	return (1);
}

int	check_argv(char *argv[])
{
	if (!is_infile(argv[1]))
		return (perror("Can't open infile"), 0);
	// if (!is_command(argv[2]) && !is_command(argv[3]))
		// return (perror("Invalid command(s)"), 0);
	if (!is_outfile(argv[4]))
		return (perror("Error, outfile does not exist"),0);
	return (1);
}

