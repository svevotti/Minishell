#include "../include/minishell.h"

char	*count_words(char *str, int *word)
{
	if (*str != 39 && *str != 34 && *str != ' '
		&& *str != '\n' && *str != '\t' && *str != '\0')
	{
		*word = 1;
		while (*str != 39 && *str != 34 && *str != ' '
			&& *str != '\n' && *str != '\t' && *str != '\0')
			str++;
	}
	else if (*str == 39)
	{
		*word = 1;
		str++;
		while (*str != 39)
			str++;
		str++;
	}
	else if (*str == 34)
	{
		*word = 1;
		str++;
		while (*str != 34)
			str++;
		str++;
	}
	return (str);
}

int	find_size_array(char *str)
{
	int	count;
	int	word;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	word = 1;
	while (*str != '\0')
	{
		count++;
		word = 1;
		while (word == 1)
		{
			word = 0;
			str = count_words(str, &word);
		}
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	}
	return (count);
}

int	find_len(char *str)
{
	int	count;
	int	single_quote;
	int	double_quotes;

	count = 0;
	single_quote = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if ((*str == ' ' || *str == '\n' || *str == '\t')
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
	return (count);
}
