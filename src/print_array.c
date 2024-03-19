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
		//printf("process %d----------\n", i + 1);
		printf("- %s\n", str[i]);
		//printf("process %d----------\n", i + 1);
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

void	print_proc_items(t_list *head)
{
	t_list *list_proc;

	list_proc = head;
	int i = 1;
	while (list_proc != NULL)
	{
		printf("--- LIST ITEM PROC %d---\n", i);
		// printf("id --> %d\n", ((t_proc *)head->content)->id);
		// printf("path --> %s\n", ((t_proc *)head->content)->path);
		// printf("cmdlist --  ");
		printf("commands --  \n");
		print_array(((t_proc *)list_proc->content)->cmd);
		// printf("pipe in --> %d\n", ((t_proc *)head->content)->pipe_in);
		// printf("pipe out --> %d\n", ((t_proc *)head->content)->pipe_out);
		// printf("infile --> %s\n", ((t_proc *)head->content)->infile);
		// printf("outfile --> %s\n", ((t_proc *)head->content)->outfile);
		// printf("no exec --> %d\n", ((t_proc *)head->content)->no_exec);
		printf("---------------\n");
		list_proc = list_proc->next;
	}
}