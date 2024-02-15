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

int check_whitespaces_front(char *str)
{
	int i;
	char	*delimiters;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{	
		if (ft_isalpha(str[i]) == 1)
			break;
		i++;
	}
	return (i);
}

int check_whitespaces_back(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (ft_isalpha(str[i]) == 1)
			return (i + 1);
		i--;
	}
	return (i);
}

int	find_size_array(char *str)
{
	int	i;
	int size;
	int count;
	int j;
	char *delimiters;

	//getting rid of extra spaces in front or back
	i = check_whitespaces_front(str);
	size = ft_strlen(str);
	if (check_whitespaces_back(str) != 0)
		size = check_whitespaces_back(str);
	//what if no input?
	count = 1;
	j = 0;
	delimiters = ft_strdup(" \n\t");
	while (str[i] != '\0' && i < size)
	{
		if (str[i] == 39)
		{
			while (str[i] != 39)
				i++;
		}
		else if(str[i] == 34)
		{
			while(str[i] != 39)
				i++;
		}
		j = 0;
		while (delimiters[j] != '\0')
		{
			if (delimiters[j] == str[i])
				count++;
			j++;
		}
		i++;
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
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	while (i < size_array)
	{
		k = 0;
		count_spaces = 0;
		size_string = find_string_size(str, &count_spaces);
		single_str = (char *)malloc(sizeof(char) * (size_string + 1));
		count = 0;
		while (count < size_string)
		{
			single_str[k] = str[l];
			l++;
			k++;
			count++;
		}
		single_str[k] = '\0';
		//printf("single str %s fir size %d\n", single_str, size_string);
		l = size_string + count_spaces;
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
		printf("%s\n", split_input[0]);
		printf("%s\n", split_input[1]);
		printf("%s\n", split_input[2]);
		//printf("%s\n", string_to_print);
		free(line);
		//free(string_to_print);
	}

	return (0);
}