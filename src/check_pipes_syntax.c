#include "../include/minishell.h"

int	check_first(char *str)
{
	int	count;
	
	count = 0;
	if (*str == '|')
	{
		while (*str == '|')
		{
			count++;
			str++;
		}
		if (count == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}

int	check_last(char *str)
{
	int	count;
	
	count = 0;
	if (*str == '|')
	{
		while (*str == '|')
		{
			count++;
			str++;
		}
		if (count == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}

int	check_pipe(char **str)
{
	int	size;

	size = find_size_input_array(str);
	if (check_first(str[0]) != 0 || check_last(str[size - 1]) != 0)
		return (ERROR);
	return (0);
}