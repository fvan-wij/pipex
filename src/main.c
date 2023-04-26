/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: flip <marvin@42.fr>                          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 00:03:38 by flip          #+#    #+#                 */
/*   Updated: 2023/04/26 17:41:00 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

// Below is a simple program which creates a child proces that starts at n=5 instead of n=0.
// The child process will first wait for the parent process to finish and then proceed to print out 5 till 10; 
//
// int main()
// {
// 	int	pid;
// 	int	n;
// 	int i;
//
// 	i = 0;
// 	pid = fork();
// 	if (pid == 0)
// 		n = 5;
// 	else
// 		n = 0;
// 	if (pid == 0)
// 		wait(EXIT_SUCCESS);
// 	if (pid == 0)
// 		i = 5;
// 	while (i < n + 5)
// 	{
// 		ft_printf("%d", i);
// 		i++;
// 	}
// 	return EXIT_SUCCESS;
// }
//

// Write a program that pipes the input from child proces to the parent proces and prints it to the terminal. 

// int main(void)
// {
// 	// When creating a pipe, the read end gets stored in fd[0] whereas the write end gets stored in fd[1];
// 	int fd[2];
// 	int pid;
// 	int i;
// 	int x;
// 	int y;
//
// 	i = 0;
// 	pipe(fd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		x = '5';
// 		write(fd[1], &x, 1);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		read(fd[0], &y, 1);
// 		write(1, &y, 1);
// 		close(fd[0]);
// 	}
// 	return (EXIT_SUCCESS);
// }

int main(int argc, char *argv[])
{
	int pid;
	int i;
	
	pid = 1;
	i = 0;
	if (argc == 5 && check_argv(argv))
		write(1, "Correct input", 13);
	else
		write(1, "Incorrect argc", 15);
	while (i < 5 && pid != 0)
	{
		pid = fork();
		i++;
	}

	if (pid == 0)
	{
		printf("I'm a child!\n");
	}
	else
	{
		waitpid(0);
		printf("I'm a parent!\n");
	}
	return EXIT_SUCCESS;
}

