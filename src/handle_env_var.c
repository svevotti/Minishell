/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:34:49 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:34:53 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(t_env *head, char *key)
{
	char	*value;

	while (head != NULL)
	{
		if (ft_strncmp(head->key, key, ft_strlen(key)) == 0)
			return (head->value);
		head = head->next;
	}
	value = (char *)malloc(sizeof(char) + 1);
	if (value == NULL)
		return (NULL);
	ft_strlcpy(value, "\0", 1);
	return (value);
}

char	*get_value(char *str, t_data *data, int *len_word)
{
	char	*name_var;
	char	*value_var;

	name_var = NULL;
	if (*str == '?')
	{
		value_var = ft_itoa(data->exitcode);
		if (value_var == NULL)
			return (NULL);
		*len_word = ft_strlen(value_var);
	}
	else
	{
		name_var = find_name_var(str);
		if (name_var == NULL)
			return (NULL);
		else
		{
			*len_word = ft_strlen(name_var);
			value_var = get_env_value(data->env, name_var);
			if (value_var == NULL)
				return (NULL);
		}
	}
	free(name_var);
	return (value_var);
}

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
	while (*str != '\0')
	{
		if (*str == '$' && flag == 0 && check_name_variable(*(str + 1)) == 1)
		{
			value_var = get_value(++str, data, &len_word);
			if (value_var == NULL)
				return (NULL);
			while (*value_var != '\0')
				*temp++ = *value_var++;
			str += len_word;
		}
		else
		{
			if (*str == 39)
				flag = get_quote_flag(flag);
			*temp++ = *str++;
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
