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
	new_string = (char *)ft_calloc(sizeof(char), str_size + 1);
	if (new_string == NULL)
		return (NULL);
	return (new_string);
}

void	copy_new_string(char *new_str, char *str, t_data *data, int flag)
{
	int		len_word;
	char	*value_var;
	char	*tmp;

	while (*str != '\0')
	{
		if (*str == '$' && flag == 0 && is_slash(str) == 0)
		{
			value_var = get_value(++str, data, &len_word);
			if (value_var == NULL)
				return ;
			tmp = value_var;
			while (*value_var != '\0')
				*new_str++ = *value_var++;
			str += len_word;
			free(tmp);
		}
		else
		{
			if (*str == 39)
				flag = get_quote_flag(flag);
			*new_str++ = *str++;
		}
	}
}

char	*expand_input(char *str, t_data *data)
{
	char	*new_string;
	int		flag_single_quote;

	new_string = get_str(str, data);
	if (new_string == NULL)
		return (NULL);
	flag_single_quote = 0;
	copy_new_string(new_string, str, data, flag_single_quote);
	return (new_string);
}
