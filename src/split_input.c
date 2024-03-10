#include "../include/minishell.h"

#define ERROR_PIPES -1
int	find_len(char *str)
{
	int	count;
	int	single_quote;
	int	double_quotes;

	count = 0;
	single_quote = 0;
	double_quotes = 0;
	if (*str == '|')
	{
		while (*str == '|')
		{
			count++;
			str++;
		}
	}
	else if (*str == '>')
	{
		while (*str == '>')
		{
			count++;
			str++;
		}
	}
	else if (*str == '<')
	{
		while (*str == '<')
		{
			count++;
			str++;
		}
	}
	else
	{
		while (*str != '\0')
		{
			if ((*str == ' ' || *str == '\n' || *str == '\t' || *str == '|' || *str == '>' || *str == '<')
				&& single_quote == 0 && double_quotes == 0)
				break ;
			if (*str == 39)
				single_quote = get_quote_flag(single_quote);
			else if (*str == 34)
				double_quotes = get_quote_flag(double_quotes);
			else
				count++;
			str++;
		}
	}
	return (count);
}

char	*get_single_str(char *str)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;

	size_string = find_len(str);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		if (*str == 39 || *str == 34)
			str++;
		else
		{
			*temp = *str;
			temp++;
			str++;
			count++;
		}
	}
	*temp = '\0';
	return (single_str);
}

char	**split_function(char *str)
{
	char	**string_split;
	int		size_array;
	int		i;
	char	*single_str;
	int		size_str;

	size_str = 0;
	size_array = find_size_array(str);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	if (string_split == NULL)
		return (NULL);
	i = 0;
	while (i < size_array)
	{
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		single_str = get_single_str(str);
		if (single_str == NULL)
			return (NULL);
		if (*str == 34 || *str == 39)
			str += 2;
		size_str = ft_strlen(single_str);
		str += size_str;
		string_split[i] = single_str;
		i++;
	}
	string_split[i] = NULL;
	return (string_split);
}
