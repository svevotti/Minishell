#include "../include/minishell.h"
#include <string.h>
#define ERROR -1
#define FREE -1
#define	PIPE_END -2
#define	ERROR_1PIPE 1
#define ERROR_2PLUSPIPE 2
#define ERROR_1REDIRECTION_INPUT 3
#define ERROR_2REDIRECTION_INPUT 4
#define ERROR_3REDIRECTION_INPUT 5
#define ERROR_4PLUSREDIRECTION_INPUT 6
#define ERROR_1REDIRECTION_OUTPUT 7
#define ERROR_2REDIRECTION_OUTPUT 8
#define ERROR_3REDIRECTION_OUTPUT 9
#define ERROR_4REDIRECTION_OUTPUT 10
#define ERROR_5PLUSREDIRECTION_OUTPUT 11

void	print_error_token(int check)
{
	if (check == ERROR_1PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (check == ERROR_2PLUSPIPE)
		printf("bash: syntax error near unexpected token `||'\n");
	else if (check == ERROR_1REDIRECTION_INPUT || check == ERROR_2REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (check == ERROR_3REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (check == ERROR_4PLUSREDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (check == ERROR_1REDIRECTION_OUTPUT || check == ERROR_2REDIRECTION_OUTPUT || check == ERROR_3REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (check == ERROR_4REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (check == ERROR_5PLUSREDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<<'\n");
}

int	check_first_argv(char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '|')
		{
			while (*str == '|')
			{
				count++;
				str++;
			}
			break ;
		}
		str++;
	}
	if (count >= 1)
	{
		if (count == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
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