/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:39:36 by joschka           #+#    #+#             */
/*   Updated: 2024/02/13 11:10:06 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*new_node(char *str)
{
	t_env	*head;

	head = malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->str = str;
	head->next = NULL;
	return (head);
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->str);
		free(head);
		head = tmp;
	}
}

void	trans_env(t_data *data, char **envp)
{
	t_env	*head;
	char	*str;
	int		i;

	str = ft_strdup(envp[0]);
	head = new_node(str);
	data->env = head;
	i = 1;
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		head->next = new_node(str);
		head = head->next;
		i++;
	}
}