#include "../include/minishell.h"

char	*traverse_quotes(char *str)
{
	char quote;

	quote = *str;
	str++;
	while (*str != quote)
		str++;
	return (str + 1);
}

char	*traverse_token(char *str)
{
	char *white_spaces = "\n\t ";


	if (!ft_strchr(white_spaces, *str) && *str != '\0' && *str != '|')
	{
		while (!ft_strchr(white_spaces, *str) && *str != '\0' && *str != '|')
		{
			if (*str == 39 || *str == 34)
				str = traverse_quotes(str);
			else
				str++;
		}
	}
	else if (*str == '|')
	{
		while (*str == '|')
			str++;
	}
	else if (*str == '>')
	{
		while (*str == '>')
			str++;
	}
	else if (*str == '<')
	{
		while (*str == '<')
			str++;
	}
	return (str);
}

int	find_size_array(char *str)
{
	int	count;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	while (*str != '\0')
	{
		count++;
		str = traverse_token(str);
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	}
	return (count);
}

