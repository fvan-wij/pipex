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

//Linked list - contains all the data necessary to run an command (e.g. path to command, additional flags, command index);
typedef struct s_cmd{ 
	struct s_cmd	*next;
	char			*cmd_path;
	char 			**cmds;
	int 			cmd_index;
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

//		Pipex_processes.c
int		spawn_child_process(t_pipex *meta, int process_count, char *envp[], int (*pipe_fd)[2]);

//		Pipex_utilities.c
void	print_cmds(t_cmd *cmd_node);
char	*ft_strchr_rev(const char *s, char c);
int		envp_path_index(char *envp[]);
int		append_node(t_cmd **head, char *cmds[], char *cmd_path, int cmd_count);

//		Pipex_error_handling.c
void	free_va_mem_and_exit(char *flags, ...);
void	free_va_mem(char *flags, ...);

//###############################################################

#endif
