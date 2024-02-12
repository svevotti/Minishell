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


int main(void)
{
	char static *line;
	char		*input_string;
	char		**array_commands;
	int			size_input_string;
	char		*string_to_print;

	int l = 0;
	while (l < 1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		add_history(line);
		input_string = line;
		size_input_string = find_size(input_string);
		string_to_print = (char *)malloc(sizeof(char) * (size_input_string + 1));
		// printf("len input %d\n", size_input_string);
		exit(1);
		l++;
		// array_commands = ft_split(line, ' ');
		// print_array(array_commands);
		free(line);
	}

	return (0);
}
