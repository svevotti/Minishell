#include "../include/minishell.h"

int	check_file_name(char *str, int size)
{
	if (*str == '>')
	{
		if (size == 1)
			print_error_token(ERROR_3REDIRECTION_INPUT);
		else
			print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
		return (ERROR);
	}
	else if (*str == '<')
	{
		if (size == 1)
			print_error_token(ERROR_4REDIRECTION_OUTPUT);
		else
			print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
		return (ERROR);
	}
	else if (*str == '|')
	{
		if (size == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}
