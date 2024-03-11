#include "../include/minishell.h"

int	check_pipe_first(char *str);
int	check_nbr_pipe(char *str);
int	check_tokens(char *str, char *next_str);
int	get_token(char *str);

int	tokens_error(char **input)
{
	int	i;

	i = 0;
	if (check_pipe_first(input[i]) != 0)
		return (ERROR);
	while (input[i] != NULL)
	{
		if (check_tokens(input[i], input[i + 1]) != 0)
			return (ERROR);
		i++;
	}
	return (0);
}

int	check_tokens(char *str, char *next_str)
{
	int	token;

	token = get_token(str);
	if (token == PIPE)
	{
		if (check_nbr_pipe(str) == -1)
			return (ERROR);
	}
	else if (token == RED_INPUT)
	{
		if (check_red_input(str, next_str) == -1)
			return (ERROR);
	}
	else if (token == RED_OUTPUT)
	{
		if (check_red_output(str, next_str) == -1)
			return (ERROR);
	}
	return (0);
}

int	get_token(char *str)
{
	if (*str == '|')
		return (1);
	else if (*str == '>')
		return (2);
	else if (*str == '<')
		return (3);
	return (0);
}

int	check_pipe_first(char *str)
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

int	check_nbr_pipe(char *str)
{
	if (ft_strlen(str) > 1)
	{
		print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}
