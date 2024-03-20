#include "../include/minishell.h"
#include <stdio.h>

void	print_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		printf("str is NULL\n");
		return ;
	}
	while (str[i] != NULL)
	{
		printf("- %s\n", str[i]);
		i++;
	}
}

void	print_3d_array(char ***str)
{
	int	i;

	i = 0;
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
	t_list	*list_proc;
	int		i;

	i = 1;
	list_proc = head;
	while (list_proc != NULL)
	{
		printf("--- LIST ITEM PROC %d---\n", i);
		printf("id --> %d\n", ((t_proc *)head->content)->id);
		printf("path --> %s\n", ((t_proc *)head->content)->path);
		printf("cmdlist --  ");
		printf("commands --  \n");
		print_array(((t_proc *)list_proc->content)->cmd);
		printf("pipe in --> %d\n", ((t_proc *)head->content)->pipe_in);
		printf("pipe out --> %d\n", ((t_proc *)head->content)->pipe_out);
		printf("infile --> %s\n", ((t_proc *)head->content)->infile);
		printf("outfile --> %s\n", ((t_proc *)head->content)->outfile);
		printf("no exec --> %d\n", ((t_proc *)head->content)->no_exec);
		printf("---------------\n");
		list_proc = list_proc->next;
	}
}

// t_list *list;

	// list = data->procs;
	// printf("-----before execution\n");
	// print_proc_items(list);
	if (is_builtin(data->procs->content) && !data->procs->next)
	{
		data->exit = 1;
		redirect(data->procs->content);
		exitcode = exec_builtin(data->procs->content, data);
		data->exit = 0;
	}
	else
		exitcode = run_executor(data);
	restore_std(data->std_in, data->std_out);
	// printf("-----after execution\n");
	// print_proc_items(list);
