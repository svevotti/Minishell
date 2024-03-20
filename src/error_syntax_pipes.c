/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:48:19 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 14:48:21 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	check_last(char *str, int len)
{
	char	*temp;
	int		pipe_number;

	if (len > 1)
	{
		pipe_number = 0;
		temp = str + len - 1;
		while (*temp == ' ' || *temp == '\t' || *temp == '\n')
			temp--;
		if (*temp == '|' && *str != 34 && *str != 39)
		{
			while (*temp == '|')
			{
				pipe_number++;
				temp--;
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
	int	len;

	if (check == 1)
	{
		len = ft_strlen(str);
		if (check_first(str) == -1 || check_last(str, len) == -1)
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
