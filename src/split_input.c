/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:23 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:35:24 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_str_count_token(char *str, int *count)
{
	if (*str == '|')
	{
		while (*str == '|')
		{
			*count = *count + 1;
			str++;
		}
	}
	else if (*str == '>')
	{
		while (*str == '>')
		{
			*count = *count + 1;
			str++;
		}
	}
	else if (*str == '<')
	{
		while (*str == '<')
		{
			*count = *count + 1;
			str++;
		}
	}
	return (str);
}

int	count_len_word(char *str)
{
	int	count;
	int	single_quote;
	int	double_quotes;

	count = 0;
	single_quote = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if ((is_white_space(str) == 1 || is_token(str) == 1)
			&& single_quote == 0 && double_quotes == 0)
			break ;
		if (*str == 39)
			single_quote = get_quote_flag(single_quote);
		else if (*str == 34)
			double_quotes = get_quote_flag(double_quotes);
		else
			count++;
		str++;
	}
	return (count);
}

int	find_len(char *str)
{
	int	count;

	count = 0;
	if (*str == '|' || *str == '>' || *str == '<')
		str = get_str_count_token(str, &count);
	else
		count = count_len_word(str);
	return (count);
}

char	*get_single_str_test(char *str, int *flag_quotes)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;

	size_string = find_len(str);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		if (*str == 39 || *str == 34)
		{
			if (*str == 39)
			{
				if (*flag_quotes == 0)
					*flag_quotes = 1;
			}
			else if (*str == 34)
			{
				if (*flag_quotes == 0)
					*flag_quotes = 1;
			}
			str++;
		}
		else
		{
			*temp = *str;
			temp++;
			str++;
			count++;
		}
	}
	*temp = '\0';
	return (single_str);
}

int	check_errors_pipes(char *str, int index, int flag_quotes, t_data *data, int size_array)
{
	int	check;
	int	size;

	check = 0;
	size = ft_strlen(str);
	if (*str == '|')
	{
		if (flag_quotes == 0) // no quotes
		{
			if (index == 0 || index == size_array - 1)
			{
				if (ft_strlen(str) == 1)
					print_error_token(ERROR_1PIPE);
				else
					print_error_token(ERROR_2PLUSPIPE);
				data->exitcode = 2;
				return (ERROR);
			}
			else
			{
				if (ft_strlen(str) > 1)
				{
					print_error_token(ERROR_2PLUSPIPE);
					data->exitcode = 2;
					return (ERROR);
				}
			}

		}
	}
	return (check);
}

char	**split_function(char *str, t_data *data)
{
	char	**string_split;
	int		size_array;
	int		i;
	char	*single_str;
	int		flag_quotes;

	flag_quotes = 0;
	size_array = find_size_array(str);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	if (string_split == NULL)
		return (NULL);
	i = 0;
	while (i < size_array)
	{
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		single_str = get_single_str_test(str, &flag_quotes);
		if (single_str == NULL)
			return (NULL);
		if (check_errors_pipes(single_str, i, flag_quotes, data, size_array) == ERROR)
			return (NULL);
		if (*str == 34 || *str == 39)
			str += 2;
		str += ft_strlen(single_str);
		string_split[i] = single_str;
		i++;
	}
	string_split[i] = NULL;
	//printf("string %s\n", string_split[0]);
	return (string_split);
}
