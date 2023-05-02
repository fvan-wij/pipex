/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 15:06:41 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/02 21:44:02 by fvan-wij      ########   odam.nl         */
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

	fd = open(outfile, O_CREAT | O_RDWR);
	if (fd < 0)
		return (0);
	return (1);
}

int	append_node(t_cmd **head, char *cmds[])
{
	t_cmd	*new_node;
	t_cmd	*current;
	int		i;	
	
	i = 0;
	current = NULL;
	new_node = malloc(1 * sizeof(t_cmd));
	if (!new_node)
		return (0);
	new_node->cmds = cmds; 
	if (!*head)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	return (1);
}

int is_command(t_pipex *meta, char *cmd, char *envp[])
{
	char	*cmd_path;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	meta->bin_path = ft_split(envp[13], ':'); 
	meta->bin_path[0] = ft_strtrim(meta->bin_path[0], "PATH=");
	while (meta->bin_path[i])	
	{
		char **argv_temp = ft_split(cmd, ' ');
		cmd_path = ft_strjoin(meta->bin_path[i], ft_strjoin("/", argv_temp[0]));
		if(access(cmd_path, X_OK) == 0 && append_node(&meta->cmd_list, argv_temp))
			return (free(cmd_path), 1);
		i++;
	}
	return (0);
}

int	parse_input(t_pipex *meta, char *argv[], char *envp[])
{
	if (!is_infile(argv[1]))
		return (perror("Can't open infile"), 0);
	if (!is_command(meta, argv[2], envp))
		return (perror("Invalid command(s)"), 0);
	if (!is_command(meta, argv[3], envp))
		return (perror("Invalid command(s)"), 0);
	if (!is_outfile(argv[4]))
		return (perror("Error, outfile does not exist"),0);
	return (1);
}

