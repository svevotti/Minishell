// #include "../include/minishell.h"
#include <stdio.h>

void print_array(char **str)
{
	int i = 0;
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}