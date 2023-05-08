/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_memory_metrics.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:44:57 by flip          #+#    #+#                 */
/*   Updated: 2023/05/08 23:03:03 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_mem allocation_metrics;

void	display_memory_usage()
{
	int	memory_usage;

	memory_usage = allocation_metrics.allocated_memory - allocation_metrics.freed_memory;
	ft_printf("Memory usage: %d bytes\n", memory_usage);
}

void	*ft_malloc(size_t size, const char str[])
{
	allocation_metrics.allocated_memory += size;
	ft_printf("%d bytes of memory allocated in %s\n", size, str);
	return malloc(size);
}

void	ft_free(void *memory, size_t size, const char str[])
{
	allocation_metrics.freed_memory += size;
	ft_printf("%d bytes of memory freed in %s\n", size, str);
	free(memory);
}

void	leaks_pipex()
{
	system("leaks pipex");
}

static void	del_cmd_path(char *cmd_path)
{
	ft_free(cmd_path, sizeof(cmd_path), "ft_clear");
}

static void	del_cmds(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		ft_free(cmds[i], sizeof(cmds[i]), "ft_clear");
		i++;
	}
}

void	ft_clear(t_cmd **lst)
{
	t_cmd	*current;

	current = *lst;
	while (current != NULL)
	{
		current = *lst;
		del_cmd_path(current->cmd_path);
		del_cmds(current->cmds);
		current = current->next;
		free(*lst);
		*lst = current;
	}
}

