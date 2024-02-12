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
	char *name_var;
	int len;
	int	i;

	i = 0;
	len = ft_strlen1(str);
	name_var = (char *)malloc(sizeof(char)*(len + 1));
	while (i < len)
	{
		if (ft_isalpha(*str) == 1)
			name_var[i] = str[i];
		else
			break;
		i++;
	}
	name_var[i] = '\0';
	return (name_var);
}

int	find_size(char *str)
{
	char	*name_var;
	int		total_len;
	char	*value_var;
	int		len_var;
	int		quote_flag;
	int		len_name_var;
	
	total_len = 0;
	len_name_var = 0;
	len_var = 0;
	quote_flag = 0;
	while (*str != '\0')
	{
		if (*str == 39)
		{
			if (quote_flag == 0)
			{
				quote_flag = 1;
			}
			else
			{
				quote_flag = 0;
			}
			str++;
		}
		else if ((*str == '$' && quote_flag == 0))
		{
			str++;
			name_var = find_name_var(str);
			len_name_var = ft_strlen(name_var);
			value_var = getenv(name_var);
			len_var = ft_strlen(value_var);
			str += len_name_var;
			total_len += len_var;
		}
		if (*str != 34)
			total_len = total_len + 1;
		str++;
	}
	return (total_len);
}