#include "../include/minishell.h"

int	find_size_pipe(char *str, t_data *data)
{
	int	count;
	int double_quotes;
	int	single_quotes;

	double_quotes = 0;
	single_quotes = 0;
	count = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	if (check_syntax_pipes(str, data, 1) == -1)
		return (ERROR);
	while (*str != '\0')
	{
		if (*str == 34)
		{
			if (single_quotes == 0)
			{
				if (double_quotes == 0)
					double_quotes = 1;
				else
					double_quotes = 0;
			}
		}
		else if (*str == 39)
		{
			if (double_quotes == 0)
			{
				if (single_quotes == 0)
					single_quotes = 1;
				else
					single_quotes = 0;
			}
		}
		if (*str == '|' && double_quotes == 0 && single_quotes == 0)
		{
			count++;
			if (check_syntax_pipes(str, data, 2) == -1)
					return (ERROR);
		}
		str++;
	}
	return (count);
}

int	count_len_process(char *str)
{
	int	count;
	int double_quotes;
	int	single_quotes;

	count = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (*str != '\0')
	{
		if (*str == '|' && single_quotes == 0 && double_quotes == 0)
			break ;
		if (*str == 34)
		{
			if (single_quotes == 0)
			{
				if (double_quotes == 0)
					double_quotes = 1;
				else
					double_quotes = 0;
			}
		}
		else if (*str == 39)
		{
			if (double_quotes == 0)
			{
				if (single_quotes == 0)
					single_quotes = 1;
				else
					single_quotes = 0;
			}
		}
		count++;
		str++;
	}
	return (count);
}

char	*get_process(char *str)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;

	size_string = count_len_process(str);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		*temp++ = *str++;
		count++;
	}
	*temp = '\0';
	return (single_str);
}

char **split_pipes(char *str, t_data *data)
{
	char	**array_processes;
	int		array_size;
	char	*process;
	int		i;

	i = 0;
	array_size = find_size_pipe(str, data);
	if (array_size == ERROR)
		return (NULL);
	array_processes = (char **)malloc(sizeof(char *) * (array_size + 1));
	if (array_processes == NULL)
		return (NULL);
	while (i < array_size)
	{
		process = get_process(str);
		if (process == NULL)
			return (NULL);
		str += ft_strlen(process) + 1;
		array_processes[i] = process;
		i++;
	}
	array_processes[i] = NULL;
	// printf("processes -----\n");
	// print_array(array_processes);
	// printf("processes -----\n");
	return (array_processes);
}
