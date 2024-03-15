/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_tokens_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:34:44 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:34:45 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	red_input_error_message(int nbr_token);
void	red_output_error_message(int nbr_token);

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
	int count;

	count = ft_strlen(str);
	if (ft_strlen(next_str) == 0)
	{
		red_input_error_message(count);
		return (ERROR);
	}
	return (0);
}

void	red_input_error_message(int nbr_token)
{
	if (nbr_token == 1 || nbr_token == 2)
		print_error_token(ERROR_REDIRECTION_INPUT);
	else if (nbr_token == 3)
		print_error_token(ERROR_3REDIRECTION_INPUT);
	else if (nbr_token > 3)
		print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
}

int	check_red_output(char *str, char *next_str)
{
	int	count;

	count = ft_strlen(str);
	if (ft_strlen(next_str) == 0)
	{
		red_output_error_message(count);
		return (ERROR);
	}
	else
	{
		if (*next_str == '|')
		{
			print_error_token(ERROR_1PIPE);
			return (ERROR);
		}
	}
	return (0);
}

void	red_output_error_message(int nbr_token)
{
	if (nbr_token == 1 || nbr_token == 2)
		print_error_token(ERROR_REDIRECTION_OUTPUT);
	else if (nbr_token == 3)
		print_error_token(ERROR_4REDIRECTION_OUTPUT);
	else if (nbr_token > 3)
		print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
}

int	get_redirection(char *str)
{
	if (ft_strlen(str) > 2)
		return (0);
	if (*str == '>')
		return(RED_INPUT);
	else if (*str == '<')
		return (RED_OUTPUT);
	return (0);
}
int	check_redirections(char **input)
{
	int	check;
	int i;

	check = 0;
	i = 0;
	while (input[i] != NULL)
	{
		if (get_redirection(input[i]) == RED_INPUT)
			check = check_red_input(input[i], input[i + 1]);
		else if (get_redirection(input[i]) == RED_OUTPUT)
			check = check_red_output(input[i], input[i + 1]);
		if (check == ERROR)
			return (ERROR);
		i++;
	}
	return (check);
}
