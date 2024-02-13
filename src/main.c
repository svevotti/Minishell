#include "../include/minishell.h"

// void print_array(char **str)
// {
// 	int i = 0;
	
// 	while (str[i] != NULL)
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// }

int	find_size_array(char *str, char *delimiter)
{
	int count;
	int	i;

	count = 0;
	i = 0;
	while (*str != '\0')
	{
		while (delimiter[i] != '\0')
		{
			if (*str == delimiter[i])
				count++;
			i++;
		}
		str++;
	}
	return (count);
}

char	*split_function(char *str, char *delimiter)
{
	char	**string_split;
	int		size_array;

	size_array = find_size_array(str, delimiter);
	printf("number of words %d\n", size_array);
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
		split_input = split_function(string_to_print, " \n\t");
		printf("%s\n", string_to_print);
		free(line);
		free(string_to_print);
	}

	return (0);
}