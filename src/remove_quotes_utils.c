/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:47:14 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 14:47:15 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_quotes(int single_quote, int double_quotes, char *str)
{
	if (*str == 39)
	{
		if (single_quote == 0 && double_quotes == 1)
			return (1);
	}
	else if (*str == 34)
	{
		if (double_quotes == 0 && single_quote == 1)
			return (1);
	}
	return (0);
}

int	find_len_str(char *str)
{
	int	count;
	int	single_quote;
	int	double_quotes;

	count = 0;
	single_quote = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if (is_white_space(str) == 1 && single_quote == 0 && double_quotes == 0)
			break ;
		if (*str == 39 || *str == 34)
		{
			get_flag(&single_quote, &double_quotes, *str);
			count = count + count_quotes(single_quote, double_quotes, str);
		}
		else
			count++;
		str++;
	}
	return (count);
}
