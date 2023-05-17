/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error_messages.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 14:48:36 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/17 15:29:04 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_cmd_not_found(char *argv)
{
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd(": Command not found\n", STDERR_FILENO);
}

void	error_file_permission(char *file)
{
	perror(file);
}
