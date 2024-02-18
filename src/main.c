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

// void	printenv(t_env *ptr)
// {
// 	while (ptr)
// 	{
// 		printf("%s ~ %s\n", ptr->key, ptr->value);
// 		ptr = ptr->next;
// 	}
// }

int main(int argc, char **argv, char **envp)
{
	char static *line;
	char		*input_string;
	int			size_input_string;
	char		*string_to_print;
	t_data		data;

	(void)argc;
	(void)argv;
	trans_env(&data, envp);
	// printenv(data.env);
	// exit(1);
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
		string_to_print = print_var(input_string, size_input_string, &data);
		printf("%s\n", string_to_print);
		free(line);
		free(string_to_print);
	}

	return (0);
}