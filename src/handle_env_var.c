/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:34:49 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 18:05:01 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_str(char *str, t_data *data)
{
	int		str_size;
	char	*new_string;

	str_size = find_size(str, data);
	if (str_size == -1)
		return (NULL);
	new_string = (char *)malloc(sizeof(char) * (str_size + 1));
	if (new_string == NULL)
		return (NULL);
	return (new_string);
}

char	*get_new_string(char *new_str, char *str, t_data *data, int flag)
{
	char	*temp;
	int		len_word;
	char	*value_var;

	temp = new_str;
	len_word = 0;
	// int count = 0;
	// int size = find_size(str, data);
	while (*str)
	{
		if (*str == '$' && flag == 0 && check_name_variable(*(str + 1)) == 1)
		{
			value_var = get_value(++str, data, &len_word);
			if (value_var == NULL)
				return (NULL);
			while (*value_var != '\0')
				*temp++ = *value_var++;
			str += len_word;
			// count += len_word;
		}
		else
		{
			if (*str == 39)
				flag = get_quote_flag(flag);
			*temp++ = *str++;
			// count++;
		}
	}
	*temp = '\0';
	return (new_str);
}

char	*expand_input(char *str, t_data *data)
{
	char	*new_string;
	int		flag_single_quote;

	new_string = get_str(str, data);
	if (new_string == NULL)
		return (NULL);
	flag_single_quote = 0;
	new_string = get_new_string(new_string, str, data, flag_single_quote);
	return (new_string);
}
