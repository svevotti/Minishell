/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:39:36 by joschka           #+#    #+#             */
/*   Updated: 2024/03/01 16:43:19 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*new_node(char *str)
{
	t_env	*node;
	char	**item;

	item = ft_split(str, '=');
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->key = ft_strdup(item[0]);
	node->value = ft_strdup(item[1]);
	node->next = NULL;
	free_array(item);
	return (node);
}

void	add_env_node(t_env **head, t_env *new)
{
	t_env	*current;

	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	trans_env(t_data *data, char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		new = new_node(envp[i]);
		add_env_node(&head, new);
		i++;
	}
	data->env = head;
}
