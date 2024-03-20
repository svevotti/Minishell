/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:47:24 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 18:42:11 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_next_str(char *str, char *next_str, int type)
{
	int	count;

	count = ft_strlen(str);
	if (next_str == NULL && type == RED_INPUT)
	{
		if (count == 1 || count == 2)
			print_error_token(ERROR_REDIRECTION_INPUT);
		else if (count == 3)
			print_error_token(ERROR_3REDIRECTION_INPUT);
		else if (count > 3)
			print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
		return (ERROR);
	}
	else if (next_str == NULL && type == RED_OUTPUT)
	{
		if (count == 1 || count == 2)
			print_error_token(ERROR_REDIRECTION_OUTPUT);
		else if (count == 3)
			print_error_token(ERROR_4REDIRECTION_OUTPUT);
		else if (count > 3)
			print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
		return (ERROR);
	}
	return (0);
}

int	check_error_redirection(char *str, int type)
{
	int	len;

	len = ft_strlen(str);
	if (len > 2)
	{
		if (type == RED_INPUT)
		{
			if (len == 3)
				print_error_token(ERROR_3REDIRECTION_INPUT);
			else if (len > 3)
				print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
			return (ERROR);
		}
		else
		{
			if (len == 3)
				print_error_token(ERROR_4REDIRECTION_OUTPUT);
			else if (len > 3)
				print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
		}
		return (ERROR);
	}
	return (0);
}

int	check_redirection_input(char *str, char *next_str, t_proc *proc)
{
	if (check_error_redirection(str, RED_INPUT) == -1)
		return (ERROR);
	if (check_next_str(str, next_str, RED_INPUT) == -1)
		return (ERROR);
	else
	{
		if (check_file_name(next_str, ft_strlen(next_str)) == -1)
			return (ERROR);
		next_str = remove_quotes(next_str);
		prepare_redirection(proc, str, next_str);
		free(next_str);
	}
	return (0);
}

int	check_redirection_output(char *str, char *next_str, t_proc *proc)
{
	if (check_error_redirection(str, RED_OUTPUT) == -1)
		return (ERROR);
	if (check_next_str(str, next_str, RED_OUTPUT) == -1)
		return (ERROR);
	else
	{
		next_str = remove_quotes(next_str);
		prepare_redirection(proc, str, next_str);
		free(next_str);
	}
	return (0);
}

int	check_syntax_redirection(char *str, char *next_str, t_proc *proc)
{
	if (*str == '>')
	{
		if (check_redirection_input(str, next_str, proc) == -1)
			return (ERROR);
	}
	else
	{
		if (check_redirection_output(str, next_str, proc) == -1)
			return (ERROR);
	}
	return (0);
}
