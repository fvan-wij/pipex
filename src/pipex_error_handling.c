/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error_handling.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 15:23:17 by flip          #+#    #+#                 */
/*   Updated: 2023/05/11 21:00:26 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	del_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	del_ll(t_cmd **lst)
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

static void	free_mem_ptr(char *flags, va_list mem_ptr)
{
	int i;
	t_cmd *temp;

	i = 0;
	temp = NULL;
	while (flags[i])
	{
		if (flags[i] == '%' && flags[i + 1] == '1' && flags[i + 2] == 'd')
			free(va_arg(mem_ptr, char *));
		else if (flags[i] == '%' && flags[i + 1] == '2' && flags[i + 2] == 'd')
			del_2d(va_arg(mem_ptr, char **));
		else if (flags[i] == '%' && flags[i + 1] == 'l' && flags[i + 2] == 'l')
		{
			temp = (t_cmd*)(va_arg(mem_ptr, t_cmd **));
			del_ll(&temp);
		}
		else if (flags[i] == '%' && flags[i + 1] == 'g' && flags[i + 2] == 'm')
			free(va_arg(mem_ptr, void *));
		else if (flags[i] == '%' && flags[i + 1] == 'p' && flags[i + 2] == 'a')
			free(va_arg(mem_ptr, int(*)[]));
		i++;
	}
}

void	free_va_mem(char *flags, ...)
{
	va_list mem_ptr;

	va_start (mem_ptr, flags);
	free_mem_ptr(flags, mem_ptr);
	va_end(mem_ptr);	
}

void	free_va_mem_and_exit(char *flags, ...)
{
	va_list mem_ptr;

	va_start (mem_ptr, flags);
	free_mem_ptr(flags, mem_ptr);
	va_end(mem_ptr);	
	exit(errno);
}

