#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "memory_metrics.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>

//######################################DATA_TYPES#########################
//ENUM		   ios: input_output_stream
typedef enum s_ios{ 
	READ,
	WRITE,
} t_ios;

//LIST		     cmd: command_linked_list
typedef struct s_cmd{ 
	int 			cmd_index;
	char			*cmd_path;
	char 			**cmds;
	struct s_cmd	*next;
} t_cmd;

//MAIN STRUCT    pipex: main struct
typedef struct s_pipex{
	char			**bin_path; 
	t_cmd			*cmd_list;
	int				cmd_count;
	int				process_count;
	char			*infile;
	char			*outfile;
} t_pipex;

//######################################SRC_FILES##########################
//Pipex_execution
int		execute_cmd(t_pipex *meta, char *envp[]);
int		find_cmd(t_cmd *cmd_list, t_cmd **node, int process_count);

//Pipex_parsing
int		parse_input(t_pipex *meta, int argc, char *argv[], char *envp[]);

//Pipex_pipes
void	close_pipes(int n, int (*pipe_array)[2]);
int		(*initialize_pipes(int n))[2];

//Pipex_processes
int		spawn_child_process(t_pipex *meta, int process_count, char *envp[], int (*pipe_fd)[]);
int		run_initial_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[], char *envp[], int process_count);
int		run_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[2], char *envp[], int process_count);
int		run_final_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[], char *envp[], int process_count);

//Pipex_utilities
void	print_cmds(t_cmd *cmd_node);
char	*ft_strchr_rev(const char *s, char c);

#endif
