#include "../include/minishell.h"
#include <stdio.h>

void print_array(char **str)
{
	int i = 0;
	if (str == NULL)
	{
		printf("str is NULL\n");
		return ;
	}
	while (str[i] != NULL)
	{
		printf("process %d----------\n", i + 1);
		printf("%s\n", str[i]);
		i++;
	}
}

void	print_3d_array(char ***str)
{
	int i = 0;
	if (str == NULL)
	{
		printf("str is NULL\n");
		return ;
	}
	while (str[i] != NULL)
	{
		printf("%d ----------\n", i);
		print_array(str[i]);
		i++;
	}
}