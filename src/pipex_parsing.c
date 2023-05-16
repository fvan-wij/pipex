/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_parsing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 15:06:41 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/16 17:16:28 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	is_infile(char *infile)
{
	int fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}


int	path_as_input(t_pipex *meta, char *cmd)
{
	char **argv_temp;
	char *cmd_path;

	argv_temp = ft_split(cmd, ' ');
	cmd_path = argv_temp[0];
	if (access(argv_temp[0], X_OK | F_OK) == -1)	
		return (0);
	else
	{
		if (ft_strncmp(argv_temp[0], "./", 2) != 0)
			argv_temp[0] = ft_strchr_rev(argv_temp[0], '/');
		return (append_node(&meta->cmd_list, argv_temp, cmd_path, meta->cmd_count));
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
			return (1);
		}
		else
			free_va_mem("%1d %2d", cmd_path, argv_temp);
		i++;
	}
	return (0);
}

int is_command(t_pipex *meta, char *cmd, char *envp[])
{
	int	path_index;

	path_index = envp_path_index(envp);
	if (path_index == -1 || cmd[0] == '/' || ft_strncmp(cmd,"./", 2) == 0)
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
		write(STDERR_FILENO, "pipex: ", 7);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		write(STDERR_FILENO, ": ", 2);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
	while (i < argc - 1)
	{
		if (i != (argc - 2) && !is_command(meta, argv[i], envp))
		{
			ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			write(STDERR_FILENO, "\n", 1);
		}
		else if (i == (argc - 2) && !is_command(meta, argv[i], envp))
		{
			ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			free_va_mem("%ll %2d %gm", meta->cmd_list, meta->bin_path, meta);
			write(STDERR_FILENO, "\n", 1);
			exit(127);
		}
		meta->cmd_count++;
		i++;
	}
	return (1);
}

