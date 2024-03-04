#include "../include/minishell.h"
int	find_key_size(char *str, char delimiter)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == delimiter)
			return (count);
		count++;
		str++;
	}
	return (count);
}

char	*get_key_str(char *str, char delimiter)
{
	int		key_size;
	char	*key;
	char	*temp;

	key_size = find_key_size(str, delimiter) + 1;
	key = (char *)malloc(sizeof(char) * (key_size + 1));
	if (key == NULL)
		return (NULL);
	temp = key;
	while (*str != '\0')
	{
		if (*str == delimiter)
		{
			str++;
			break ;
		}
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (key);
}

char	*get_value_str(char *str)
{
	int		value_size;
	char	*value;
	char	*temp;

	value_size = ft_strlen(str);
	value = (char *)malloc(sizeof(char) * (value_size + 1));
	if (value == NULL)
		return (NULL);
	temp = value;
	while (*str != '\0')
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (value);
}

char	**get_item(char *str, char delimiter)
{
	char	**split_env;
	char	*key;
	char	*value;

	split_env = (char **)malloc(sizeof(char *) * 3);
	if (split_env == NULL)
		return (NULL);
	key = get_key_str(str, delimiter);
	if (key == NULL)
		return (NULL);
	str = str + ft_strlen(key) + 1;
	value = get_value_str(str);
	// if (value == NULL)
	// 	return (NULL);
	split_env[0] = ft_strdup(key);
	if (value == NULL)
		split_env[1] = NULL;
	else
		split_env[1] = ft_strdup(value);
	split_env[2] = NULL;
	return (split_env);
}
