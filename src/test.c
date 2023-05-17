#include <stdlib.h>
#include <unistd.h>

typedef	int t_pipes[2];

t_pipes	*initialize_pipes(int n)
{
	t_pipes	*pipe_fd;
	int		i;

	pipe_fd = malloc(n * sizeof(int [2]));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pipe(pipe_fd[i]);
		i++;
	}
	return (pipe_fd);
}

void	f()
{
	system("leaks a.out");
}

int main()
{
	t_pipes *pipe_fd;

	atexit(f);
	pipe_fd = initialize_pipes(2);
	// free(pipe_fd);
}
