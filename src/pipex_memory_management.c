/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_memory_management.c                         :+:    :+:             */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 15:23:17 by flip          #+#    #+#                 */
/*   Updated: 2023/05/18 16:05:13 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	del_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	del_ll(t_cmd **lst)
{
	t_cmd	*current;

	current = *lst;
	while (current != NULL)
	{
		current = *lst;
		free(current->cmd_path);
		del_2d(current->cmds);
		current = current->next;
		free(*lst);
		*lst = current;
	}
}

void	del_pipes(t_pipes *pipe_fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

void	free_pipex(t_pipex *meta, int exit_code)
{
	if (meta->cmd_list)
		del_ll(&meta->cmd_list);
	if (meta)
		free(meta);
	exit (exit_code);
}
