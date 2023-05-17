/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 16:18:33 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/17 16:59:30 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//############################HEADERS############################

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
//---------------------------------------------------------------
//############################DATA_TYPES#########################

//Enumerator - defines the read and write end of a pipe;
typedef enum s_ios{
	READ,
	WRITE,
}	t_ios;

//Enumerator - defines error messages;
typedef enum s_err{
	ERR_ALLOCATION,
	ERR_PERMISSION,
	ERR_CMD_NOT_FOUND,
	ERR_REDIRECTION,
	ERR_EXECUTION,
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
}	t_pipex;

// typedef	int t_pipes[2];

//###############################################################
//---------------------------------------------------------------
//#############################SRC_FILES#########################

//		Pipex_execution.c
int		execute_cmd(t_pipex *meta, char *envp[], int (*pipe_fd)[2], pid_t *pid);
int		find_cmd(t_cmd *cmd_list, t_cmd **node, int process_count);

//		Pipex_parsing.c
int		parse_input(t_pipex *meta, int argc, char *argv[], char *envp[]);

//		Pipex_pipes.c
void	close_pipes(int n, int (*pipe_fd)[2]);
int		(*initialize_pipes(int n))[2];
// t_pipes *initialize_pipes(int n);

//		Pipex_processes.c
int		spawn_child_process(t_pipex *meta, int process_count,
			char *envp[], int (*pipe_fd)[2]);

//		Pipex_redirection.c 
int		redirect_init_child(int infile, int (*pipe_fd)[2],
			t_pipex *meta, int process_count);
int		redirect_child(int (*pipe_fd)[2], t_pipex *meta,
			int process_count);
int		redirect_final_child(int outfile, int (*pipe_fd)[2],
			t_pipex *meta, int process_count);

//		Pipex_utilities.c
void	print_cmds(t_cmd *cmd_node);
char	*ft_strchr_rev(const char *s, char c);
int		envp_path_index(char *envp[]);
int		append_node(t_cmd **head, char *cmds[], char *cmd_path, int cmd_count);

//		Pipex_memory_management.c
void	free_pipex(t_pipex *meta, int exit_code);
void	del_2d(char **arr);
void	del_ll(t_cmd **lst);

//		Pipex_error_messages.c
void	error_cmd_not_found(char *argv);
void	error_file_permission(char *file);

//###############################################################

#endif
