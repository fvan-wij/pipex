/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_memory_management.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 15:23:17 by flip          #+#    #+#                 */
/*   Updated: 2023/05/17 15:31:40 by fvan-wij      ########   odam.nl         */
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

void	free_pipex(t_pipex *meta, int exit_code)
{
	if (meta->bin_path)
		del_2d(meta->bin_path);
	if (meta->cmd_list)
		del_ll(&meta->cmd_list);
	if (meta)
		free(meta);
	exit (exit_code);
}
