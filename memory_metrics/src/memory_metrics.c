/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_metrics.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 21:44:57 by flip          #+#    #+#                 */
/*   Updated: 2023/05/09 11:47:20 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory_metrics.h"

static t_mem allocation_metrics;

void	display_memory_usage()
{
	int	memory_usage;

	memory_usage = allocation_metrics.allocated_memory - allocation_metrics.freed_memory;
	printf("Memory usage: %d bytes\n", memory_usage);
}

void	*ft_malloc(size_t size, const char str[])
{
	allocation_metrics.allocated_memory += size;
	printf("%ld bytes of memory allocated in %s\n", size, str);
	return malloc(size);
}

void	ft_free(void *memory, size_t size, const char str[])
{
	allocation_metrics.freed_memory += size;
	printf("%ld bytes of memory freed in %s\n", size, str);
	free(memory);
}

void	leaks_pipex()
{
	system("leaks pipex");
}

void	del_single_arr(char *arr, char const str[])
{
	ft_free(arr, sizeof(arr), str);
	printf("%ld bytes of memory freed in %s\n", sizeof(arr), str);
}

void	del_double_arr(char **arr, char const str[])
{
	size_t bytes;
	int i;

	i = 0;
	bytes = 0;
	while (arr[i])
	{
		free(arr[i]);
		bytes += sizeof(arr[i]);
		i++;
	}
	// ft_free(arr, sizeof(arr), "del_double_arr");
	free(arr);
	bytes += sizeof(arr);
	allocation_metrics.freed_memory += bytes;
	printf("%ld bytes of memory freed in %s\n", bytes, str);
}

// void	ft_clear(t_cmd **lst)
// {
// 	t_cmd	*current;
//
// 	current = *lst;
// 	while (current != NULL)
// 	{
// 		current = *lst;
// 		del_cmd_path(current->cmd_path);
// 		del_cmds(current->cmds);
// 		current = current->next;
// 		free(*lst);
// 		*lst = current;
// 	}
// }

