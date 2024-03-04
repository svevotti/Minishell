#include "../include/minishell.h"

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

char	*move_str(char *str)
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
	return (str);
}

char	**split_function(char *str)
{
	char	**string_split;
	int		size_array;
	int		i;
	char	*single_str;

	i = 0;
	size_array = find_size_array(str);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	if (string_split == NULL)
		return (NULL);
	while (i < size_array)
	{
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		single_str = get_single_str(str);
		if (single_str == NULL)
			return (NULL);
		str = move_str(str);
		string_split[i] = single_str;
		str++;
		i++;
	}
	string_split[i] = NULL;
	return (string_split);
}
