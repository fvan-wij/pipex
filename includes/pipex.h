#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <string.h>

typedef enum s_ios{
	READ,
	WRITE,
} t_ios;

typedef struct s_cmd{
	int 			cmd_index;
	char 			**cmds;
	char			*cmd_path;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_pipex{
	char			**bin_path;
	t_cmd			*cmd_list;
	int				cmd_count;
	int				process_count;
	char			*infile;
	char			*outfile;
} t_pipex;

int		parse_input(t_pipex *meta, int argc, char *argv[], char *envp[]);

int	(*initialize_pipes(int n))[2];
int	execute_cmd(t_pipex *meta, char *envp[]);
int	find_cmd(t_cmd *cmd_list, t_cmd **node, int process_count);

// int	spawn_child_process(t_pipex *meta, int process_count, char *envp[], int pipe_fd[]);
// int	run_initial_child_process(t_pipex *meta, t_cmd *cmd_node, int pipe_fd[], char *envp[]);
// int	run_child_process(t_cmd *cmd_node, int pipe_fd[], char *envp[]);
// int run_final_child_process(t_pipex *meta, t_cmd *cmd_node, int pipe_fd[], char *envp[]);

int	spawn_child_process(t_pipex *meta, int process_count, char *envp[], int (*pipe_fd)[]);
int	run_initial_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[], char *envp[], int process_count);
int	run_child_process(t_cmd *cmd_node, int (*pipe_fd)[], char *envp[], int process_count);
int run_final_child_process(t_pipex *meta, t_cmd *cmd_node, int (*pipe_fd)[], char *envp[], int process_count);
#endif
