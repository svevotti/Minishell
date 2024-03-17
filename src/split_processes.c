#include "../include/minishell.h"

int	check_first(char *str)
{
	int	pipe_number;

	pipe_number = 0;
	if (*str == '|')
	{
		while (*str == '|')
		{
			pipe_number++;
			str++;
		}
		if (pipe_number == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}

int	check_last(char *str)
{
	char *temp;
	int	pipe_number;

	pipe_number = 0;	
	temp = str + ft_strlen(str) - 1;
	while (*temp == ' ' || *temp == '\t' || *temp == '\n')
		temp--;
	if (*temp == '|')
	{
		while (*temp == '|')
		{
			pipe_number++;
			temp--;;
		}
		if (pipe_number == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}

int	check_number(char *str)
{
	int	pipe_number;

	pipe_number = 0;
	while (*str == '|')
	{
		pipe_number++;
		str++;
	}
	if (pipe_number > 1)
	{
		if (pipe_number == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}

int	check_syntax_pipes(char *str, t_data *data, int check)
{
	if (check == 1)
	{
		if (check_first(str) == - 1 || check_last(str) == -1)
		{
			data->exitcode = 2;
			return (ERROR);
		}
	}
	else
	{
		if (check_number(str) == -1)
		{
			data->exitcode = 2;
			return (ERROR);
		}
	}
	return (0);
}

int	find_size_pipe(char *str, t_data *data)
{
	int	count;
	int	single_quote;
	int	double_quote;

	count = 1;
	single_quote = 0;
	double_quote = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	if (check_syntax_pipes(str, data, 1) == -1)
		return (ERROR);
	while (*str != '\0')
	{
		if (*str == '|')
		{
			count++;
			if (check_syntax_pipes(str, data, 2) == -1)
				return (ERROR);
		}
		// if (*str == 39)
		// {
		// 	if (single_quote == 0)
		// 		single_quote = get_quote_flag(single_quote);
		// }
		// else if (*str == 34)
		// {
		// 	if (double_quote == 0)
		// 		double_quote = get_quote_flag(double_quote);
		// }
		// else if (*str == '|' && single_quote == 0 && double_quote == 0)
		// {
		// 	count++;
		// 	if (check_syntax_pipes(str, data, 2) == -1)
		// 		return (ERROR);
		// }
		str++;
	}
	return (count);
}

int	count_len_process(char *str)
{
	int	count;
	int	single_quote;
	int	double_quotes;

	count = 0;
	single_quote = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if (*str == '|' && single_quote == 0 && double_quotes == 0)
			break ;
		// else if (*str == 39)
		// {
		// 	if (single_quote == 0)
		// 		single_quote = get_quote_flag(single_quote);
		// 	else
		// 		count++;
		// }
		// else if (*str == 34)
		// {
		// 	if (double_quotes == 0)
		// 		double_quotes = get_quote_flag(double_quotes);
		// 	else
		// 		count++;
		// }
		// else
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
	int	single_quote;
	int	double_quotes;

	single_quote = 0;
	double_quotes = 0;
	size_string = count_len_process(str);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		// if (*str == 39 || *str == 34)
		// {
		// 	if (*str == 39)
		// 	{
		// 		if (single_quote == 0)
		// 			single_quote = 1;
		// 		if (double_quotes == 0)
		// 			str++;
		// 		else
		// 		{
		// 			*temp++ = *str++;
		// 			count++;
		// 		}
		// 	}
		// 	else if (*str == 34)
		// 	{
		// 		if (double_quotes == 0)
		// 			double_quotes = 1;
		// 		if (single_quote == 0)
		// 			str++;
		// 		else
		// 		{
		// 			*temp++ = *str++;
		// 			count++;
		// 		}
		// 	}
		// }
		// else
		// {
			*temp++ = *str++;
			count++;
		// }
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
	return (array_processes);
}