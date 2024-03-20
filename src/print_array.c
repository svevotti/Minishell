/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:47:40 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 14:47:41 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
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
