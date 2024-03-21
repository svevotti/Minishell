/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:48:02 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 14:48:03 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(t_env *head, char *key)
{
	char	*value;

	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (ft_strdup(head->value));
		head = head->next;
	}
	value = (char *)malloc(sizeof(char) + 1);
	if (value == NULL)
		return (NULL);
	ft_strlcpy(value, "\0", 1);
	return (value);
}

char	*create_exitcode(t_data *data, int *len_word)
{
	char	*value_var;

	value_var = ft_itoa(data->exitcode);
	if (value_var == NULL)
		return (NULL);
	*len_word = 1;
	return (value_var);
}

char	*get_value(char *str, t_data *data, int *len_word)
{
	char	*name_var;
	char	*value_var;

	name_var = NULL;
	if (*str == '?')
	{
		value_var = create_exitcode(data, len_word);
		if (value_var == NULL)
			return (NULL);
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
