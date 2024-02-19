/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:39:36 by joschka           #+#    #+#             */
/*   Updated: 2024/02/19 10:52:51 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_key_size(char *str, char delimiter)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == delimiter)
			break ;
		count++;
		str++;
	}
	return (count);
}

char	**custom_split(char *str, char delimiter)
{
	char	**split_env;
	int		key_size;
	int		value_size;
	char	*key;
	char	*value;
	char	*temp;

	//printf("trans env line 49 str %s\n", str);
	split_env = (char **)malloc(sizeof(char *) * 3);
	key_size = find_key_size(str, delimiter);
	//printf("trans env line 52 key size %d\n", key_size);
	key = (char *)malloc(sizeof(char) * (key_size + 1));
	//printf("trans first char for value %c\n", str[key_size]);
	value_size = ft_strlen(str + key_size + 1);
	value = (char *)malloc(sizeof(char) * (value_size + 1));
	temp = key;
	while (*str != '\0')
	{
		//printf("trans line 58 %s\n", str);
		if (*str == delimiter)
		{
			str++;
			temp++;
			break;
		}
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	//printf("trans env line 68 key %s\n", key);
	temp = value;
	while (*str != '\0')
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	//printf("tr//ans env line 82 value %s\n", value);
	split_env[0] = ft_strdup(key);
	split_env[1] = ft_strdup(value);
	split_env[2] = NULL;
	//exit(1);
	return (split_env);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_env	*new_node(char *str)
{
	t_env	*node;
	char	**item;
	
	//item = ft_split(str, '=');
	item = custom_split(str, '=');
	//print_array(item);
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
		while(current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

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