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
} t_pipex;

int		parse_input(t_pipex *meta, int argc, char *argv[], char *envp[]);
int		execute_cmd(t_pipex *meta, int process_count, char *envp[], int pipe_fd[]);

#endif
