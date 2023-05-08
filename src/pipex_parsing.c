/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_parsing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 15:06:41 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/08 23:00:43 by flip          ########   odam.nl         */
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

int	append_node(t_cmd **head, char *cmds[], char *cmd_path, int cmd_count)
{
	t_cmd	*new_node;
	t_cmd	*current;
	
	current = NULL;
	new_node = NULL;
	new_node = ft_malloc(sizeof(t_cmd), "append_node");
	if (!new_node)
		return (0);
	new_node->cmds = cmds;
	new_node->cmd_path = cmd_path;
	new_node->cmd_index = cmd_count;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (1);
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

int is_command(t_pipex *meta, char *cmd, char *envp[])
{
	char	*cmd_path;
	int		path_index;
	int		i;
	
	i = 0;
	path_index = envp_path_index(envp);
	meta->bin_path = ft_split(envp[path_index], ':');
	meta->bin_path[0] = ft_strtrim(meta->bin_path[0], "PATH=");
	while (meta->bin_path[i])	
	{
		char **argv_temp = ft_split(cmd, ' ');
		cmd_path = ft_strjoin(meta->bin_path[i], ft_strjoin("/", argv_temp[0]));
		if(access(cmd_path, X_OK) == 0 && append_node(&meta->cmd_list, argv_temp, cmd_path, meta->cmd_count))
		{
			meta->cmd_count++;
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_input(t_pipex *meta, int argc, char *argv[], char *envp[])
{
	int	i;

	i = 2;
	if (!is_infile(argv[1]))
		return (perror("Can't open infile"), 0);
	while (i < argc - 1)
	{
		if (!is_command(meta, argv[i], envp))
			return (0);
		// if (i == (argc - 1) && is_command(meta, argv[i], envp))
		// 	return (0);
		i++;
	}
	return (1);
}

