#include "../include/minishell.h"

char	*get_str_count_token(char *str, int *count)
{
	if (*str == '>')
	{
		while (*str == '>')
		{
			*count = *count + 1;
			str++;
		}
	}
	else if (*str == '<')
	{
		while (*str == '<')
		{
			*count = *count + 1;
			str++;
		}
	}
	return (str);
}

void	count_len_word(char *str, int *count)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*str != '\0')
	{
		if (is_white_space(str) == 1 && single_q == 0 && double_q == 0)
			break ;
		else if (*str == 39)
		{
			double_q = get_quote_flag(double_q);
			if (double_q == 0)
				single_q = get_quote_flag(single_q);
		}
		else if (*str == 34)
		{
			single_q = get_quote_flag(single_q);
			if (single_q == 0)
				double_q = get_quote_flag(double_q);
		}
		*count = *count + 1;
		str++;
	}
}

int	find_len_token(char *str)
{
	int	count;

	count = 0;
	if (is_token(str) == 1)
		str = get_str_count_token(str, &count);
	else
		count_len_word(str, &count);
	return (count);
}

char	*get_single_str(char *str)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;

	size_string = find_len_token(str);
	if (size_string == -1)
		return (NULL);
	if (size_string == -1)
		return (NULL);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
			*temp++ = *str++;
			count++;
	}
	*temp = '\0';
	return (single_str);
}
