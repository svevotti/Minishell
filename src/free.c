/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:48:20 by joschka           #+#    #+#             */
/*   Updated: 2024/03/20 14:40:57 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->str);
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_procs(t_list *procs)
{
	t_list	*tmp;

	while (procs)
	{
		tmp = procs->next;
		free_list(((t_proc *)procs->content)->cmdlist);
		free_array(((t_proc *)procs->content)->cmd);
		if (((t_proc *)procs->content)->infile)
			free(((t_proc *)procs->content)->infile);
		if (((t_proc *)procs->content)->outfile)
			free(((t_proc *)procs->content)->outfile);
		free(procs->content);
		free(procs);
		procs = tmp;
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_data(t_data *data)
{
	free_procs(data->procs);
	free_array(data->input);
	free_env(data->env);
}
