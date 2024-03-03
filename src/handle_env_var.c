#include "../include/minishell.h"

char	*get_env_value(t_env *head, char *key)
{
	while (head != NULL)
	{
		if (ft_strncmp(head->key, key, ft_strlen(key)) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	*get_value(char *str, t_env *env, int *len_word)
{
	char	*name_var;
	char	*value_var;

	if (*str == '?')
	{
		value_var = ft_itoa(env->exit_status);
		if (value_var == NULL)
			return (NULL);
		*len_word = 1;
	}
	else
	{
		name_var = find_name_var(str);
		if (name_var == NULL)
			return (NULL);
		*len_word = ft_strlen(name_var);
		value_var = get_env_value(env, name_var);
	}
	return (value_var);
}

char	*get_str(char *str, t_env *env)
{
	int		str_size;
	char	*new_string;

	str_size = find_size(str, env);
	if (str_size == -1)
		return (NULL);
	new_string = (char *)malloc(sizeof(char) * (str_size + 1));
	if (new_string == NULL)
		return (NULL);
	return (new_string);
}

char	*expand_input(char *str, t_data *data)
{
	char	*new_string;
	char	*temp;
	int		flag_single_quote;
	int		len_word;
	char	*value_var;

	new_string = get_str(str, data->env);
	if (new_string == NULL)
		return (NULL);
	temp = new_string;
	flag_single_quote = 0;
	len_word = 0;
	while (*str != '\0')
	{
		if (*str == '$' && flag_single_quote == 0)
		{
			value_var = get_value(++str, data->env, &len_word);
			while (*value_var != '\0')
				*temp++ = *value_var++;
			str += len_word;
		}
		else
		{
			if (*str == 39)
				flag_single_quote = get_single_quote_flag(flag_single_quote);
			*temp++ = *str++;
		}
	}
	*temp = '\0';
	return (new_string);
}
