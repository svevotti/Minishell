#include "../include/minishell.h"

void	red_input_error_message(int nbr_token, int next_word_len);
void	red_output_error_message(int nbr_token, int next_word_len);

void	print_error_token(int check)
{
	if (check == ERROR_1PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	else if (check == ERROR_2PLUSPIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
	else if (check == ERROR_REDIRECTION_INPUT)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (check == ERROR_3REDIRECTION_INPUT)
		ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
	else if (check == ERROR_4PLUSREDIRECTION_INPUT)
		ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
	else if (check == ERROR_REDIRECTION_OUTPUT)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (check == ERROR_4REDIRECTION_OUTPUT)
		ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
	else if (check == ERROR_5PLUSREDIRECTION_OUTPUT)
		ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
}

int	check_red_input(char *str, char *next_str)
{
	int	count;

	count = ft_strlen(str);
	if (ft_strlen(next_str) == 0)
	{
		red_input_error_message(count, 0);
		return (ERROR);
	}
	else
	{
		if (count >= 3)
		{
			red_input_error_message(count, 1);
			return (ERROR);
		}
	}
	return (0);
}

void	red_input_error_message(int nbr_token, int next_word_len)
{
	if (next_word_len == 0)
	{
		if (nbr_token == 1 || nbr_token == 2)
			print_error_token(ERROR_REDIRECTION_INPUT);
		else if (nbr_token == 3)
			print_error_token(ERROR_3REDIRECTION_INPUT);
		else if (nbr_token > 3)
			print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
	}
	else
	{
		if (nbr_token == 3)
			print_error_token(ERROR_3REDIRECTION_INPUT);
		else
			print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
	}
}

int	check_red_output(char *str, char *next_str)
{
	int	count;

	count = ft_strlen(str);
	if (ft_strlen(next_str) == 0)
	{
		red_output_error_message(count, 0);
		return (ERROR);
	}
	else
	{
		if (count >= 3)
		{
			red_output_error_message(count, 1);
			return (ERROR);
		}
	}
	return (0);
}

void	red_output_error_message(int nbr_token, int next_word_len)
{
	if (next_word_len == 0)
	{
		if (nbr_token == 1 || nbr_token == 2)
			print_error_token(ERROR_REDIRECTION_OUTPUT);
		else if (nbr_token == 3)
			print_error_token(ERROR_4REDIRECTION_OUTPUT);
		else if (nbr_token > 3)
			print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
	}
	else
	{
		if (nbr_token == 3)
			printf("error to check\n");
		else if (nbr_token == 4)
			print_error_token(ERROR_4REDIRECTION_OUTPUT);
		else
			print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
	}
}
