#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

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
	// t_pipes *pipe_fd;

	// atexit(f);
	// pipe_fd = initialize_pipes(2);
	char string[] = "Hey I always say: 'What is up'";
	char **temp;
	int	i;

	temp = ft_split_quotations(string, ' ');
	
	ft_printf("temp: %s\n", temp[4]);
	// i = 0;
	// {
	// 	while (temp[i]) 
	// 	ft_printf("temp[%d]: %s\n", temp[i]);
	// 	i++;
	// }
}
