#include "../include/minishell.h"

void print_array(char **str)
{
	int i = 0;
	
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	find_size_array(char *str)
{
	int count;
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
			if (*str != 39 && *str != 34 && *str != ' ' && *str != '\n' && *str != '\t' && *str != '\0')
			{
				word = 1;
				while (*str != 39 && *str != 34 && *str != ' ' && *str != '\n' && *str != '\t' && *str != '\0')
					str++;
			}
			else if (*str == 39)
			{
				word = 1;
				str++;
				while (*str != 39)
					str++;
				str++;
			}
			else if (*str == 34)
			{
				word = 1;
				str++;
				while (*str != 34)
					str++;
				str++;
			}
		}
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	}
	return (count);
}

int find_len(char *str)
{
	int count;
	int	single_quote;
	int	double_quotes;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	single_quote = 0;
	double_quotes = 0;
	int i = 0;
	while (*str != '\0')
	{
		if ((*str == ' ' || *str == '\n' || *str == '\t') && single_quote == 0 && double_quotes == 0)
			break ;
		if (*str == 39)
		{
			if (single_quote == 0)
				single_quote = 1;
			else
				single_quote = 0;
		}
		else if (*str == 34)
		{
			if (double_quotes == 0)
				double_quotes = 1;
			else
				double_quotes = 0;
		}
		else
			count++;
		str++;
	}
	return (count);
}

char	**split_function(char *str)
{
	char	**string_split;
	int		size_array;
	int		i;
	int		size_string;
	int		count_spaces;
	int		k;
	int		l;
	int		count;
	char 	*single_str;
	int		str_len;
	char	*temp;

	i = 0;
	l = 0;
	size_string = 0;
	size_array = find_size_array(str);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	while (i < size_array)
	{
		size_string = find_len(str);
		single_str = (char *)malloc(sizeof(char) * (size_string + 1));
		count = 0;
		temp = single_str;
		while (count < size_string)
		{
			if (*str == 39 || *str == 34)
				str++;
			else if (*str == ' ' || *str == '\n' || *str == '\t')
			{
				while (*str == ' ' || *str == '\n' || *str == '\t')
					str++;
			}
			else 
			{
				*temp = *str;
				temp++;
				str++;
				count++;
			}
		}
		*temp = '\0';
		string_split[i] = single_str;
		str++;
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		i++;
	}
	string_split[i] = NULL;
	return(string_split);
}

int main(void)
{
	char static *line;
	char		*input_string;
	int			size_input_string;
	char		*string_to_print;
	char		**split_input;

	while (1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		if (ft_strncmp(line, "clear", 5) == 0)
		{
			free(line);
			exit(1);
		}
		add_history(line);
		// input_string = line;
		// size_input_string = find_size(input_string);
		// string_to_print = print_env_var(input_string, size_input_string);
		split_input = split_function(line);
		print_array(split_input);
		// printf("%s\n", string_to_print);
		free(line);
		//free(string_to_print);
	}

	return (0);
}