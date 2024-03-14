/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_split_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:37:23 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:37:24 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_size_input_array(char **array)
{
	int	i;

	i = 0;
	while (*array != NULL)
	{
		array++;
		i++;
	}
	return (i);
}

char	*traverse_quotes(char *str)
{
	char	quote;

	quote = *str;
	str++;
	while (*str != quote)
		str++;
	return (str + 1);
}

char	*move_according_token(char *str)
{
	if (*str == '|')
	{
		while (*str == '|')
			str++;
	}
	else if (*str == '>')
	{
		while (*str == '>')
			str++;
	}
	else if (*str == '<')
	{
		while (*str == '<')
			str++;
	}
	return (str);
}

char	*traverse_token(char *str)
{
	char	*white_spaces;

	white_spaces = ("\n\t ");
	if (!ft_strchr(white_spaces, *str) && *str != '\0' && *str != '|'
		&& *str != '>' && *str != '<')
	{
		while (!ft_strchr(white_spaces, *str) && *str != '\0'
			&& *str != '|' && *str != '>' && *str != '<')
		{
			if (*str == 39 || *str == 34)
				str = traverse_quotes(str);
			else
				str++;
		}
	}
	else if (*str == '|' || *str == '>' || *str == '<')
		str = move_according_token(str);
	return (str);
}

int	find_size_array(char *str)
{
	int	count;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	while (*str != '\0')
	{
		count++;
		str = traverse_token(str);
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	}
	return (count);
}
