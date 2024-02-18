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

int find_string_size(char *str)
{
	int count;
	int word;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	word = 1;
	while (*str != '\0')
	{
		word = 1;
		while (word == 1)
		{
			word = 0;
			if (*str != 39 && *str != 34 && *str != ' ' && *str != '\n' && *str != '\t' && *str != '\0')
			{
				word = 1;
				while (*str != 39 && *str != 34 && *str != ' ' && *str != '\n' && *str != '\t' && *str != '\0')
				{
					count++;
					str++;
				}
			}
			else if (*str == 39)
			{
				word = 1;
				str++;
				while (*str != 39)
				{
					if (*str == ' ' || *str == '\n' || *str == '\t')
					{
						while (*str == ' ' || *str == '\n' || *str == '\t')
							str++;
					}
					else
					{
						count++;
						str++;
					}
				}
				str++;
			}
			else if (*str == 34)
			{
				word = 1;
				str++;
				while (*str != 34)
				{
					if (*str == ' ' || *str == '\n' || *str == '\t')
					{
						while (*str == ' ' || *str == '\n' || *str == '\t')
							str++;
					}
					else
					{
						count++;
						str++;
					}
				}
				str++;
			}
		}
		if (*str == ' ' || *str == '\n' || *str == '\t')
			break ;
	}
	return (count);
}

int check_number_quotes(char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == 39 || *str == 34)
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
	int		flag;
	int		max_quotes;

	i = 0;
	l = 0;
	size_string = 0;
	size_array = find_size_array(str);
	printf("size array %d\n", size_array);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	while (i < size_array)
	{
		size_string = find_string_size(str);
		printf("size string %d\n", size_string);
		single_str = (char *)malloc(sizeof(char) * (size_string + 1));
		count = 0;
		k = 0;
		flag = 0;
		while (count < size_string)
		{
			max_quotes = check_number_quotes(str);
			if (str[l] == 39 || str[l] == 34)
			{
				if (flag == max_quotes)
					break ;
				l++;
			}
			else if (str[l] == ' ' || str[l] == '\n' || str[l] == '\t')
			{
				while (str[l] == ' ' || str[l] == '\n' || str[l] == '\t')
					l++;
			}
			else 
			{
				single_str[k] = str[l];
				k++;
				l++;
				count++;
			}
		}
		single_str[k] = '\0';
		string_split[i] = ft_strdup(single_str);
		free(single_str);
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