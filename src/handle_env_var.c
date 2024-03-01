#include "../include/minishell.h"

int	ft_strlen1(char *str)
{
	int len;

	len = 0;
	while (*str != '\0')
	{
		if (ft_isalpha(*str) == 1)
			len++;
		else
			break;
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

int	get_len_value_var(char *str, int *len_name_var, t_env *env)
{
	int		exit_status;
	char	*name_var;
	char	*value_var;
	int		len_var;

	exit_status = 0;
	len_var = 0;
	if (*str == '?')
	{
		exit_status = env->exit_status;
		value_var = ft_itoa(exit_status);
		len_var = ft_strlen(value_var);
		*len_name_var = 1;
	}
	else
	{
		name_var = find_name_var(str);
		if (name_var == NULL)
			return (-1);
		*len_name_var = ft_strlen(name_var);
		value_var = getenv(name_var);
		len_var = len_var + ft_strlen(value_var);
	}
	return (len_var);
}

void	get_quote_flag(int *quote_flag, int *total_len)
{
	
	if (*quote_flag == 0)
		*quote_flag = 1;
	else
		*quote_flag = 0;
	*total_len = *total_len - 1;
}

int	find_size(char *str, t_env *env)
{
	int		total_len;
	int		len_var;
	int		quote_flag;
	int		len_name_var;
	
	total_len = 0;
	len_name_var = 0;
	len_var = 0;
	quote_flag = 0;
	while (*str != '\0')
	{	
		if (*str == '$' && quote_flag == 0)
		{
			len_var = get_len_value_var(str + 1, &len_name_var, env);
			if (len_var == -1)
				return (-1);
			str += len_name_var + 1;
			total_len += len_var;
		}
		else
		{
			if (*str == 39)
				get_quote_flag(&quote_flag, &total_len);
			total_len += 1;
			str++;
		}
		if (*str == 34)
			total_len -= 2;
	}
	printf("tot size %d\n", total_len);
	return (total_len);
}

char *get_env_value(t_env *head, char *key)
{
	while (head != NULL)
	{
		if (ft_strncmp(head->key, key, ft_strlen(key)) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char *expand_input(char *str, t_data *data)
{
	char *new_string;
	int	i;
	int	j;
	int	flag_single_quote;
	char	*name_var;
	char	*value_var;
	int		len_var;
	int k;
	int str_size;

	str_size = find_size(str, data->env);
	if (str_size == -1)
		return (NULL);
	new_string = (char *)malloc(sizeof(char) * (str_size + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	j = 0;
	flag_single_quote = 0;
	len_var = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
		{
			if (flag_single_quote == 0)
				flag_single_quote = 1;
			else
				flag_single_quote = 0;
			i++;
		}
		else if (str[i] == 34)
			i++;
		else if (str[i] == '$' && flag_single_quote == 0)
		{
			k = 0;
			i++;
			if (str[i] == '?')
			{
				int exit_status = data->env->exit_status;
				name_var = (char *)malloc(sizeof(char) * (1 + 1));
				strlcpy(name_var, "?", 2);
				value_var = ft_itoa(exit_status);
				len_var = ft_strlen(value_var);

			}
			else
			{
				name_var = find_name_var(str + i);
				value_var = get_env_value(data->env, name_var);
				len_var = ft_strlen(value_var);
			}
			while (k < len_var)
			{
				new_string[j] = value_var[k];
				j++;
				k++;	
			}
			i += ft_strlen(name_var);
		}
		else
		{
			new_string[j] = str[i];
			j++;
			i++;
		}
		new_string[j] = '\0';
	}
	return (new_string);
}