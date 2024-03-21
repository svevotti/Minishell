/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_size_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:35 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:35:37 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_len_var(char *str, int *len_name_var, t_data *data)
{
	char	*name_var;
	char	*value_var;
	int		len_var;

	name_var = NULL;
	if (*str == '?')
	{
		value_var = ft_itoa(data->exitcode);
		if (value_var == NULL)
			return (-1);
		len_var = ft_strlen(value_var);
		*len_name_var = 1;
	}
	else
	{
		name_var = find_name_var(str);
		if (name_var == NULL)
			return (-1);
		*len_name_var = ft_strlen(name_var);
		value_var = get_env_value(data->env, name_var);
		len_var = ft_strlen(value_var);
	}
	free(name_var);
	free(value_var);
	return (len_var);
}

int	find_size(char *str, t_data *data)
{
	int		total_len;
	int		quote_flag;
	int		len_name_var;

	total_len = 0;
	quote_flag = 0;
	while (*str != '\0')
	{
		if (*str == '$' && quote_flag == 0)
		{
			total_len += get_len_var(str + 1, &len_name_var, data);
			if (total_len == -1)
				return (-1);
			str += len_name_var;
		}
		else if (*str == 39)
		{
			quote_flag = get_quote_flag(quote_flag);
			total_len += 1;
		}
		else
			total_len += 1;
		str++;
	}
	return (total_len);
}
