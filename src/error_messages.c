#include "../include/minishell.h"
#include <string.h>
#define ERROR -1
#define FREE -1
#define	PIPE_END -2
#define	ERROR_1PIPE 1
#define ERROR_2PLUSPIPE 2
#define ERROR_REDIRECTION_INPUT 1
#define ERROR_3REDIRECTION_INPUT 3
#define ERROR_4PLUSREDIRECTION_INPUT 4
#define ERROR_REDIRECTION_OUTPUT 1
#define ERROR_4REDIRECTION_OUTPUT 4
#define ERROR_5PLUSREDIRECTION_OUTPUT 5

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

int	pipe_token(char *str)
{
	int	count;

	count = 0;
	while (*str == '|')
	{
		count++;
		str++;
	}
	return (count);
}

int	red_input(char *str)
{
	int	count;

	count = 0;
	while (*str == '>')
	{
		count++;
		str++;
	}
	return (count);
}

int	red_output(char *str)
{
	int	count;

	count = 0;
	while (*str == '<')
	{
		count++;
		str++;
	}
	return (count);
}

int	check_first_argv(char *str)
{
	int count;
	int	token;

	count = 0;
	while (*str != '\0')
	{
		token = get_token(str);
		if (token == 1)
		{
			count = pipe_token(str);
			if (count >= 1)
			{
				if (count == 1)
					print_error_token(ERROR_1PIPE);
				else
					print_error_token(ERROR_2PLUSPIPE);
				return (ERROR);
			}
		}
		else if (token == 2)
		{
			count = red_input(str);
			if (count >= 3)
			{
				if (count == 3)
					print_error_token(ERROR_3REDIRECTION_INPUT);
				else
					print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
				return (ERROR);
			}

		}
		else if (token == 3)
		{
			count = red_output(str);
			if (count >= 4)
			{
				if (count == 4)
					print_error_token(ERROR_4REDIRECTION_OUTPUT);
				else
					print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
				return (ERROR);
			}

		}
		str++;
	}
	return (0);
}

int	check_tokens_error(char **input)
{
	int i;
	char	*box;
	int		count;

	i = 0;
	count = 0;
	if (check_first_argv(input[i]) == ERROR)
		return (ERROR);
	while (input[i] != NULL)
	{
		box = input[i];
		while (*box != '\0')
		{
			if (*box == '|')
			{
				while (*box == '|')
				{
					count++;
					box++;
				}
				break ;
			}
			box++;
		}
		i++;
	}
	if (count > 1)
	{
		print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}