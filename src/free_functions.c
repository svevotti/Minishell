#include "../include/minishell.h"

void	free_input(char **input)
{
	int	i;

	i = 0;
	while (input != NULL)
	{
		free(input[i]);
		i++;
	}
	free(input);
}

int	free_strings(char *str1, char *str2, char **str3)
{
	free(str1);
	free(str2);
	if (str3 != NULL)
		free_input(str3);
	else
		(void)str3;
	return (1);
}
