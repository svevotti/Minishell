#include "../include/minishell.h"

int	ft_strlen1(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		if (ft_isalpha(*str) == 1)
			len++;
		else
			break ;
		str++;
	}
	return (len);
}

char	*find_name_var(char *str)
{
	char	*name_var;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen1(str);
	name_var = (char *)malloc(sizeof(char) * (len + 1));
	if (name_var == NULL)
		return (NULL);
	while (i < len)
	{
		if (ft_isalpha(str[i]) == 1)
			name_var[i] = str[i];
		else
			break ;
		i++;
	}
	name_var[i] = '\0';
	return (name_var);
}

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

char	*expand_input(char *str, t_data *data)
{
	char	*new_string;
	char	*temp;
	int		flag_single_quote;
	char	*name_var;
	char	*value_var;
	int		str_size;

	str_size = find_size(str, data->env);
	if (str_size == -1)
		return (NULL);
	new_string = (char *)malloc(sizeof(char) * (str_size + 1));
	if (new_string == NULL)
		return (NULL);
	temp = new_string;
	flag_single_quote = 0;
	while (*str != '\0')
	{
		if (*str == '$' && flag_single_quote == 0)
		{
			str++;
			if (*str == '?')
				value_var = ft_itoa(data->env->exit_status;);
			else
			{
				name_var = find_name_var(str);
				value_var = get_env_value(data->env, name_var);
			}
			while (*value_var != '\0')
				*temp++ = *value_var++;
			str += ft_strlen(name_var);
		}
		else
		{
			if (*str == 39)
				flag_single_quote = flag_single_quote == 1 ? 0 : 1;
			*temp++ = *str++;
		}
	}
	*temp = '\0';
	return (new_string);
}
