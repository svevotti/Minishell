#include "../include/minishell.h"
#include <string.h>
#define ERROR -1
#define	ERROR_1PIPE -1
#define ERROR_2PLUSPIPE -2
#define ERROR_REDIRECTION_INPUT -3
#define ERROR_3REDIRECTION_INPUT -4
#define ERROR_4PLUSREDIRECTION_INPUT -5
#define ERROR_REDIRECTION_OUTPUT -6
#define ERROR_4REDIRECTION_OUTPUT -7
#define ERROR_5PLUSREDIRECTION_OUTPUT -8
#define PIPE 1
#define RED_INPUT 2
#define RED_OUTPUT 3

void	print_error_token(int check)
{
	if (check == ERROR_1PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (check == ERROR_2PLUSPIPE)
		printf("bash: syntax error near unexpected token `||'\n");
	else if (check == ERROR_REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (check == ERROR_3REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (check == ERROR_4PLUSREDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (check == ERROR_REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (check == ERROR_4REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (check == ERROR_5PLUSREDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<<'\n");
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
	int count;

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

int	check_tokens(char *str, char *next_str)
{
	int	count;
	int	token;

	count = 0;
	token = get_token(str);
	if (token == PIPE)
	{
		if (ft_strlen(str) > 1)
		{
			print_error_token(ERROR_2PLUSPIPE);
			return (ERROR);
		}
	}
	else if (token == RED_INPUT)
	{
		count = ft_strlen(str);
		if (ft_strlen(next_str) == 0)
		{
			if (count == 1 || count == 2)
				print_error_token(ERROR_REDIRECTION_INPUT);
			else if (count == 3)
					print_error_token(ERROR_3REDIRECTION_INPUT);
			else if (count > 3)
				print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
			return (ERROR);
		}
		else
		{
			if (count >= 3)
			{
				if (count == 3)
					print_error_token(ERROR_3REDIRECTION_INPUT);
				else
					print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
				return (ERROR);
			}
		}
	}
	else if (token == RED_OUTPUT)
	{
		count = ft_strlen(str);
		if (ft_strlen(next_str) == 0)
		{
			if (count == 1 || count == 2)
				print_error_token(ERROR_REDIRECTION_OUTPUT);
			else if (count == 3)
				printf("error to check\n");
			else if (count == 4)
				print_error_token(ERROR_4REDIRECTION_OUTPUT);
			else if (count > 4)
				print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
			return (ERROR);
		}
		else
		{
			if (count >= 3)
			{
				if (count == 3)
					printf("error to check\n");
				else if (count == 4)
					print_error_token(ERROR_4REDIRECTION_OUTPUT);
				else
					print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
				return (ERROR);
			}
		}
	}
	return (0);
}

int	tokens_error(char **input)
{
	int i;

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