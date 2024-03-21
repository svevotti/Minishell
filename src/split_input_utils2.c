/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:47:53 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 14:47:54 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_str_count_token(char *str, int *count)
{
	if (*str == '>')
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
		printf("c %c\n", *str);
		if ((is_white_space(str) == 1 || is_token(str) == 1)
			&& single_quote == 0 && double_quotes == 0)
			break ;
		else if (*str == 39 || *str == 34)
			get_flag(&single_quote, &double_quotes, *str);
		count++;
		str++;
	}
	return (count);
}

int	find_len_token(char *str)
{
	int	count;

	count = 0;
	if (is_token(str) == 1)
		str = get_str_count_token(str, &count);
	else
		count = count_len_word(str);
	return (count);
}

char	*get_single_str(char *str)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;

	size_string = find_len_token(str);
	printf("string size %d\n", size_string);
	if (size_string == -1)
		return (NULL);
	if (size_string == -1)
		return (NULL);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		*temp++ = *str++;
		count++;
	}
	*temp = '\0';
	return (single_str);
}
