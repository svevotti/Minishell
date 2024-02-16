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
	int len_str = 0;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	int word = 1;
	int l = 0;
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
				while (*str != 39 || word == 1)
				{
					if (*str == 39)
					{
						str++;
						break;
					}
					str++;
				}
			}
			else if (*str == 34)
			{
				word = 1;
				while (*str != 34 || word == 1)
				{
					if (*str == 34)
					{
						str++;
						break;
					}
					str++;
				}
			}
		}
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		l++;
	}
	return (count);
}

int find_string_size(char *str, int *l)
{
	int i;
	char *delimiters;
	int	j;
	int	flag;
	int m;

	
	flag = 0;
	i = 0;
	delimiters = ft_strdup(" \n\t");
	while (str[i] != '\0')
	{
		j = 0;
		while (delimiters[j] != '\0')
		{
			if (delimiters[j] == str[i])
			{
				*l = 1;
				m = i;
				while(ft_isalpha(str[m]) == 0)
				{
					*l = *l + 1;
					m++;
				}
				*l = *l - 1;
				return (i);
			}
			j++;
		}
		i++;
	}
	return (i);
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

	i = 0;
	l = 0;
	size_string = 0;
	size_array = find_size_array(str);
	printf("size array %d\n", size_array);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	while (i < size_array)
	{
		k = 0;
		count_spaces = 0;
		size_string = find_string_size(str, &count_spaces);
		// printf("size array %d\n", size_string);
		single_str = (char *)malloc(sizeof(char) * (size_string + 1));
		count = 0;
		while (count < size_string)
		{
			single_str[k] = str[l];
			l++;
			k++;
			count++;
		}
		// printf("last char %c\n", str[l]);
		single_str[k] = '\0';
		string_split[i] = ft_strdup(single_str);
		free(single_str);
		while (str[l] == ' ' || str[l] == '\n' || str[l] == '\t')
			l++;
		//printf("single str %s fir size %d\n", single_str, size_string);
		//printf("size array %d - i %d\n", size_array, i);
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
		// print_array(split_input);
		// printf("%s\n", string_to_print);
		free(line);
		//free(string_to_print);
	}

	return (0);
}