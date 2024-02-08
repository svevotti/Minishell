#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include "../include/minishell.h"
#include <readline/history.h>

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
	char		**array_commands;

	while (1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		add_history(line);
		array_commands = ft_split(line, ' ');
		print_array(array_commands);
		free(line);
	}

	return (0);
}