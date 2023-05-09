/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_metrics.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 10:56:33 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/09 11:47:22 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_METRICS_H
# define MEMORY_METRICS_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_mem{
	int	allocated_memory;
	int	freed_memory;

} t_mem;

// Memory metrics

void	display_memory_usage();
void	*ft_malloc(size_t size, const char str[]);
void	ft_free(void *memory, size_t size ,const char str[]);
void	ft_clear(void **lst);
void	leaks_pipex();
void	del_single_arr(char *arr, char const str[]);
void	del_double_arr(char **arr, char const str[]);

#endif
