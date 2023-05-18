/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_parsing.c                                   :+:    :+:             */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 15:06:41 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/18 16:21:15 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	path_as_input(t_pipex *meta, char *cmd)
{
	char	**argv_temp;
	char	*cmd_path;

	argv_temp = ft_split(cmd, ' ');
	cmd_path = ft_strdup(argv_temp[0]);
	if (access(argv_temp[0], X_OK | F_OK) == -1)
	{
		free(cmd_path);
 		del_2d(argv_temp);
		return (0);
	}
	else if (ft_strncmp(argv_temp[0], "./", 2) != 0)
	{
		ft_memmove(argv_temp[0], ft_strchr_rev(argv_temp[0], '/'), ft_strlen(argv_temp[0]));
		if (append_node(&meta->cmd_list, argv_temp, cmd_path, meta->cmd_count) == 0)
			free_pipex(meta, ERR_ALLOCATION);
		return (1);
	}
	return (0);
}

static char *append_cmd_to_path(char *bin_path, char *argv_temp)
{
	char	*cmd_temp;
	char	*join_temp;
	char	*cmd_path;

	join_temp = ft_strjoin("/", argv_temp); //Appends a forward slash to argv[0] (e.g. argv[0] wc will become argv[0] /wc);
	cmd_temp = ft_strjoin(bin_path, join_temp);
	cmd_path = ft_strdup(cmd_temp); //Results in path + /cmd appended;
	free(join_temp);
	free(cmd_temp);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

static int	cmd_as_input(t_pipex *meta, char *cmd, char *envp[], int path_index)
{
	int		i;
	char	*cmd_path;
	char	**argv_temp;

	i = 0;
	meta->bin_path = ft_split(envp[path_index], ':');
	ft_memmove(meta->bin_path[0], ft_strchr(meta->bin_path[0], '/'), ft_strlen(ft_strchr(meta->bin_path[0], '/')));
	argv_temp = ft_split(cmd, ' '); //Splits argv on white space (e.g. "wc -l" resulting in argv[0] wc, argv[1] -l);
	while (meta->bin_path[i])
	{
		cmd_path = append_cmd_to_path(meta->bin_path[i], argv_temp[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			del_2d(meta->bin_path);
			if (append_node(&meta->cmd_list, argv_temp, cmd_path, meta->cmd_count) == 0)
				free_pipex(meta, ERR_ALLOCATION);
			return (1);
		}
		else
			free(cmd_path);
		i++;
	}
	del_2d(argv_temp);
	return (0);
}

static int	is_command(t_pipex *meta, char *cmd, char *envp[])
{
	int	path_index;

	path_index = envp_path_index(envp);
	if (path_index == -1 || cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0)
		return (path_as_input(meta, cmd));
	else
		return (cmd_as_input(meta, cmd, envp, path_index));
}

static void	exit_accordingly(t_pipex *meta)
{
	int	fd;

	fd = open(meta->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(meta->outfile);
		free_pipex(meta, 1);
	}
	else
		free_pipex(meta, 127);
}

int	parse_input(t_pipex *meta, int argc, char *argv[], char *envp[])
{
	int	i;

	i = 2;
	while (i < argc - 1)
	{
		if (i != (argc - 2) && !is_command(meta, argv[i], envp))
			error_cmd_not_found(argv[i]);
		else if (i == (argc - 2) && !is_command(meta, argv[i], envp))
		{
			error_cmd_not_found(argv[i]);
			exit_accordingly(meta);
		}
		meta->cmd_count++;
		i++;
	}
	return (1);
}
