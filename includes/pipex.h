/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 16:18:33 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/19 14:35:27 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//###############################################################
//---------------------------HEADERS-----------------------------
//###############################################################

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

//###############################################################
//--------------------------DATA_TYPES---------------------------
//###############################################################

//Enumerator - defines the read and write end of a pipe;
typedef enum s_ios{
	READ,
	WRITE,
}	t_ios;

//Enumerator - defines error messages;
typedef enum s_err{
	ERR,
	ERR_ALLOCATION,
	ERR_PERMISSION,
	ERR_CMD_NOT_FOUND,
	ERR_REDIRECTION,
	ERR_EXECUTION,
	ERR_ARGC_COUNT,
	ERR_FORK,
}	t_err;

//Linked list - contains all the data necessary to run an command
//				(e.g. path to command, additional flags, command index);
typedef struct s_cmd{
	struct s_cmd	*next;
	char			*cmd_path;
	char			**cmds;
	int				cmd_index;
}	t_cmd;

//Main struct - contains all meta data
typedef struct s_pipex{
	t_cmd			*cmd_list;
	char			**bin_path;
	char			*infile;
	char			*outfile;
	int				cmd_count;
	int				process_count;
	char			**envp;
}	t_pipex;

//Typedef array of pipes - used to create an array of pipes without confusing
//						   the fuck out of people due to weird syntax;
typedef int	t_pipes[2];

//###############################################################
//--------------------------SRC_FILES----------------------------
//###############################################################

//		Pipex_execution.c
int		execute_cmd(t_pipex *meta, t_pipes *pipe_fd, pid_t *pid);
int		find_cmd(t_cmd *cmd_list, t_cmd **node, int process_count);

//		Pipex_parsing.c
int		parse_input(t_pipex *meta, int argc, char *argv[]);

//		Pipex_pipes.c
void	close_pipes(int n, t_pipes *pipe_fd);
// int		(*initialize_pipes(int n))[2];
t_pipes	*initialize_pipes(int n);

//		Pipex_processes.c
int		spawn_child_process(t_pipex *meta, int process_count,
			t_pipes *pipe_fd);

//		Pipex_redirection.c 
int		redirect_init_child(int infile, t_pipes *pipe_fd,
			t_pipex *meta, int process_count);
int		redirect_child(t_pipes *pipe_fd, t_pipex *meta,
			int process_count);
int		redirect_final_child(int outfile, t_pipes *pipe_fd,
			t_pipex *meta, int process_count);

//		Pipex_utilities.c
void	print_cmds(t_cmd *cmd_node);
char	*ft_strchr_rev(const char *s, char c);
int		envp_path_index(char *envp[]);
int		append_node(t_cmd **head, char *cmds[], char *cmd_path, int cmd_count);

//		Pipex_memory_management.c
void	del_pipes(t_pipes *pipe_fd, int n);
void	del_ll(t_cmd **lst);
void	del_2d(char **arr);
void	exit_pipex(t_pipex *meta, int exit_code);
void	exit_due_final_cmd_failure(t_pipex *meta);

//		Pipex_error_messages.c
void	error_cmd_not_found(char *argv);
void	error_file_permission(char *file);

//###############################################################
//---------------------------------------------------------------
//###############################################################

#endif
