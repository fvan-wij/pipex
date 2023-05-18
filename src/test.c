#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <stdio.h>

typedef	int t_pipes[2];

int	skip_delimiter_till_text(char const *s, char c, int *i)
{
	while (s[*i] == c && s[*i])
		(*i)++;
}

int	skip_text_till_delimiter(char const *s, char c, int *i)
{
	while (s[*i] != c && s[*i])
		(*i)++;
}

int skip_text_till_end_of_quotations(char const *s, char c, int *i)
{
	while (s[*i])
	{
		(*i)++;
		if (s[*i] == 39)	
			return ((*i)++);
	}
}

static int	word_counter(char const *s, char c)
{
	int		i;
	int		w_count;

	i = 0;
	w_count = 0;
	skip_delimiter_till_text(s, c, &i);
	while (s[i]) // 					"Hoe 'gaat het?'";
	{
		if (s[i] == 39)
			skip_text_till_end_of_quotations(s, c, &i);
		else
			skip_text_till_delimiter(s, c, &i);
		w_count++;
		skip_delimiter_till_text(s, c, &i);
	}
	return (w_count);
}

static char **free_substrings(char **strings_array, int j)
{
	while (j >= 0)
	{
		free(strings_array[j]);
		j--;
	}
	free(strings_array);
}

static int	word_length(char const *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static int	sentence_length(char const *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i] != 39 && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static char	**split_words(char **str_array, char const *s, char c, int words)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (j < words && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == 39)
		{
			i++;
			len = sentence_length(s, i, 39);
		}
		else
			len = word_length(s, i, c);
		str_array[j] = ft_substr(s, i, len);
		if (!str_array[j])
		{
			str_array = free_substrings(str_array, j);
			return (0);
		}
		i += len;
		j++;
	}
	return (str_array);
}

char	**ft_split_quotations(char const *s, char c)
{
	char	**str_array;
	int		words;

	words = word_counter(s, c);
	str_array = ft_calloc(words + 1, sizeof(char *));
	if (!str_array)
		return (0);
	str_array = split_words(str_array, s, c, words);
	if (!str_array)
		return (0);
	return (str_array);
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
	char string[] = "Hoe 'gaat het?' kaas";
	// printf("wc is: %d\n", word_counter(string, ' '));
	char **temp;
	int	i;

	temp = ft_split_quotations(string, ' ');

	// ft_printf("temp: %s\n", temp[3]);
		i = 0;
		while (temp[i]) 
		{
			ft_printf("temp[%d]: %s\n", i, temp[i]);
			i++;
		}
}
