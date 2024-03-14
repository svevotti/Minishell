/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:37 by joschka           #+#    #+#             */
/*   Updated: 2024/03/11 13:39:42 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*var_exists(char *str, t_env *env)
{
	char	*ident;

	ident = get_identifier(str);
	while (env)
	{
		if (!ft_strcmp(ident, env->key))
		{
			free(ident);
			return (env);
		}
		env = env->next;
	}
	free(ident);
	return (NULL);
}

int	check_var(char *str, t_env *env)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] != '=')
		return (-1);
	if (var_exists(str, env))
		return (2);
	return (0);
}

void	expand_env(char *str, t_env *env)
{
	t_env	*new;

	new = new_node(str);
	add_env_node(&env, new);
}

int	del_var(char *str, t_data *data)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = "unset";
	cmd[1] = get_identifier(str);
	cmd[2] = NULL;
	ft_unset(cmd, data);
	free(cmd[1]);
	free(cmd);
	return (0);
}

int	ft_export(char **cmd, t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (!cmd[i])
		ft_env(data->env);
	while (cmd[i])
	{
		ret = check_var(cmd[i], data->env);
		if (ret == 1)
			export_error(cmd[i]);
		else if (ret == 2)
			ret = del_var(cmd[i], data);
		if (!ret)
			expand_env(cmd[i], data->env);
		i++;
	}
	if (ret == -1)
		ret = 0;
	return (ret);
}
