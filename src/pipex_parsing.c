/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_parsing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 15:06:41 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/11 13:34:14 by flip          ########   odam.nl         */
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

int	path_as_input(t_pipex *meta, char *cmd)
{
	char **argv_temp;
	char *cmd_path;

	argv_temp = ft_split(cmd, ' ');
	cmd_path = argv_temp[0];
	if (access(argv_temp[0], X_OK) == -1)	
	{
		printf("Yeet\n");
		// printf("argv_temp[0]: %s\n", argv_temp[0]);
		return (0);
	}
	else
	{
		argv_temp[0] = ft_strchr_rev(argv_temp[0], '/');
		if (!append_node(&meta->cmd_list, argv_temp, cmd_path, meta->cmd_count))
			return (0);
		else {
			meta->cmd_count++;
			return (1);
		}
	}
}

int	cmd_as_input(t_pipex *meta, char *cmd, char *envp[], int path_index)
{
	int	i;
	char *cmd_path;
	char **argv_temp;

	i = 0;
	meta->bin_path = ft_split(envp[path_index], ':');
	meta->bin_path[0] = ft_strtrim(meta->bin_path[0], "PATH=");
	while (meta->bin_path[i])	
	{
		argv_temp = ft_split(cmd, ' ');
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

int is_command(t_pipex *meta, char *cmd, char *envp[])
{
	int	path_index;

	path_index = envp_path_index(envp);
	if (path_index == -1 || cmd[0] == '/')
		return (path_as_input(meta, cmd));
	else
		return (cmd_as_input(meta, cmd, envp, path_index));
}

int	parse_input(t_pipex *meta, int argc, char *argv[], char *envp[])
{
	int	i;

	i = 2;
	if (!is_infile(argv[1]))
	{
		perror("pipex");
		exit (1);
	}
	while (i < argc - 1)
	{
		if (!is_command(meta, argv[i], envp))
		{
			ft_free(meta, sizeof(t_pipex), "parse_input");
			ft_printf("pipex: command not found: %s\n", argv[i]);
			exit (127);
		}
		i++;
	}
	return (1);
}

