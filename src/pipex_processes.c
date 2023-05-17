/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/05 18:33:47 by flip          #+#    #+#                 */
/*   Updated: 2023/05/17 17:59:01 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	run_initial_child_process(t_pipex *meta, t_cmd *cmd_node,
		t_pipes *pipe_fd, char *envp[], int process_count)
{
	int	infile;

	infile = open(meta->infile, O_RDONLY);
	if (infile < 0)
	{
		error_file_permission(meta->infile);
		free_pipex(meta, ERR_PERMISSION);
	}
	if (redirect_init_child(infile, pipe_fd, meta, process_count) == -1)
		free_pipex(meta, ERR_REDIRECTION);
	if (execve(cmd_node->cmd_path, cmd_node->cmds, envp) == -1)
		free_pipex(meta, ERR_EXECUTION);
}

static void	run_child_process(t_pipex *meta, t_cmd *cmd_node,
		t_pipes *pipe_fd, char *envp[], int process_count)
{
	redirect_child(pipe_fd, meta, process_count);
	if (execve(cmd_node->cmd_path, cmd_node->cmds, envp) == -1)
		free_pipex(meta, ERR_EXECUTION);
}

static void	run_final_child_process(t_pipex *meta, t_cmd *cmd_node,
		t_pipes *pipe_fd, char *envp[], int process_count)
{
	int	outfile;

	outfile = open(meta->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		error_file_permission(meta->outfile);
		close_pipes(meta->cmd_count - 1, pipe_fd);
		free_pipex(meta, ERR_PERMISSION);
	}
	if (redirect_final_child(outfile, pipe_fd, meta, process_count) == -1)
		free_pipex(meta, ERR_REDIRECTION);
	if (execve(cmd_node->cmd_path, cmd_node->cmds, envp) == -1)
		free_pipex(meta, ERR_EXECUTION);
}

int	spawn_child_process(t_pipex *meta, int process_count,
		char *envp[], t_pipes *pipe_fd)
{
	t_cmd	*cmd_node;

	if (!find_cmd(meta->cmd_list, &cmd_node, process_count))
		free_pipex(meta, 127);
	if (!cmd_node)
		free_pipex(meta, ERR_CMD_NOT_FOUND);
	if (process_count == 0)
		run_initial_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	else if (process_count != 0 && process_count != (meta->cmd_count - 1))
		run_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	else
		run_final_child_process(meta, cmd_node, pipe_fd, envp, process_count);
	return (-1);
}
