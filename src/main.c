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
	printf("str %s\n", str);
	while (str[i] != '\0')
	{	
		printf("i %d\n", i);
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

int find_string_size(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
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
}
char	*split_function(char *str)
{
	char	**string_split;
	int		size_array;

	size_array = find_size_array(str);
	printf("number of words %d\n", size_array);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	while (string_split[i] != '\0' && i < size_array)
	{
			size_string = find_string_size(str);
			string_split[i] = (char *)malloc(sizeof(char) * (size_string + 1));
			while ()
		

		i++;
	}
	print_array(string_split);
	exit(1);

	return(NULL);
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
		printf("%s\n", string_to_print);
		free(line);
		free(string_to_print);
	}

	return (0);
}