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
	int 			index;
	char 			**cmds;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_pipex{
	char			**bin_path;
	t_cmd			*cmd_list;
} t_pipex;

int	parse_input(t_pipex *meta, char *argv[], char *envp[]);

#endif
