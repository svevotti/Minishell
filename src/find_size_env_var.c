#include "../include/minishell.h"

int	check_double_quotes(char *str)
{
	while (*str != '\0')
	{
		if (*str == 34)
			return (-2);
		str++;
	}
	return (0);
}

int	get_len_var(char *str, int *len_name_var, t_env *env)
{
	char	*name_var;
	char	*value_var;
	int		len_var;

	len_var = check_double_quotes(str);
	if (*str == '?')
	{
		value_var = ft_itoa(env->exit_status);
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
		value_var = getenv(name_var);
		len_var = len_var + ft_strlen(value_var);
	}
	return (len_var);
}

int	get_quote_flag(int *quote_flag)
{
	if (*quote_flag == 0)
		*quote_flag = 1;
	else
		*quote_flag = 0;
	return (1);
}

int	find_size(char *str, t_env *env)
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
			total_len += get_len_var(str + 1, &len_name_var, env);
			if (total_len == -1)
				return (-1);
			str += len_name_var;
		}
		else if (*str == 39)
			quote_flag = quote_flag == 1 ? 0 : 1;
		else
			total_len += 1;
		str++;
	}
	return (total_len);
}
