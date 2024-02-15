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

int main(void)
{
	char static *line;
	char		*input_string;
	int			size_input_string;
	char		*string_to_print;

	while (1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			exit(1);
		}
		add_history(line);
		input_string = line;
		size_input_string = find_size(input_string);
		string_to_print = print_variable(input_string, size_input_string);
		printf("%s\n", string_to_print);
		free(line);
		free(string_to_print);
	}

	return (0);
}