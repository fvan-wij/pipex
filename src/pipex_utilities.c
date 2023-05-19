/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utilities.c                                 :+:    :+:             */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 14:45:13 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/19 14:27:54 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_cmds(t_cmd *cmd_node)
{
	int	i;

	i = 1;
	printf("--> cmd#%d [%s ", cmd_node->cmd_index, cmd_node->cmds[0]);
	while (cmd_node->cmds[i])
	{
		printf("%s", cmd_node->cmds[i]);
		i++;
	}
	printf("]\n");
}

char	*ft_strchr_rev(const char *s, char c)
{
	int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == c)
			return ((char *)s + (i + 1));
		i--;
	}
	return (NULL);
}

int	envp_path_index(char *envp[])
{
	int	path_index;

	path_index = 0;
	while (envp[path_index])
	{
		if (ft_strnstr(envp[path_index], "PATH=", 5))
			return (path_index);
		path_index++;
	}
	return (-1);
}

int	append_node(t_cmd **head, char *cmds[], char *cmd_path, int cmd_count)
{
	t_cmd	*new_node;
	t_cmd	*current;

	current = NULL;
	new_node = NULL;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (ft_putstr_fd("Allocation error: failed to \
					allocate memory for 't_cmd node'\n", STDERR_FILENO), 0);
	new_node->next = NULL;
	new_node->cmds = cmds;
	new_node->cmd_path = cmd_path;
	new_node->cmd_index = cmd_count;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current && current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (1);
}
