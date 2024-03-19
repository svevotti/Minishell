/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:34:35 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:34:36 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_count_redirection(char *str, t_data *data, int type)
{
	int check;

	check = ft_strlen(str);
	if (check > 2)
	{
		if (type == 1)
		{
			if (check == 3)
				print_error_token(ERROR_3REDIRECTION_INPUT);
			else if (check > 3)
				print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
		}
		else
		{
			if (check == 3)
				print_error_token(ERROR_4REDIRECTION_OUTPUT);
			else if (check > 3)
				print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
		}
		data->exitcode = 2;
		return (ERROR);
	}
	return (check);
}

int	check_syntax_tokens(char *str, t_data *data, int size_array)
{
	int check;

	check = 0;
	if (data->flag_quotes == 0)
	{
		if (*str == '>')
			check = check_count_redirection(str, data, RED_INPUT);
		else if (*str == '<')
			check = check_count_redirection(str, data, RED_OUTPUT);
	}
	return (check);
}
