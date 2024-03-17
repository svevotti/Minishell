#include "../include/minishell.h"

int	check_first(char *str)
{
	int	pipe_number;

	pipe_number = 0;
	if (*str != 34 || *str != 39)
	{
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
	if (*str != 34 || *str != 39)
	{
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
	}
	return (0);
}

int	check_number(char *str)
{
	int	pipe_number;

	pipe_number = 0;
	if (*str == 34 || *str == 39)
	{
		str++;
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