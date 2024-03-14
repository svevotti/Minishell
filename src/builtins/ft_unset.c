/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:26:02 by joschka           #+#    #+#             */
/*   Updated: 2024/03/11 13:38:40 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->str);
	free(node->value);
	free(node);
}

void	del_env_node(t_env **previous, t_env *current)
{
	(*previous)->next = current->next;
	free_env_node(current);
}

void	ft_unset(char **cmd, t_data *data)
{
	int		i;
	t_env	*run;

	i = 1;
	while (cmd[i])
	{
		run = data->env;
		if (!ft_strcmp(cmd[i], run->key))
		{
			data->env = data->env->next;
			free_env_node(run);
			run = data->env;
		}
		while (run->next)
		{
			if (!ft_strcmp(cmd[i], run->next->key))
				del_env_node(&run, run->next);
			else
				run = run->next;
		}
		i++;
	}
}
