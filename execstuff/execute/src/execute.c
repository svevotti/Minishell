/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:40:05 by joschka           #+#    #+#             */
/*   Updated: 2024/02/13 13:08:14 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*get_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*cmdpath;
	char	*tmp;
	int		i;

	while (ft_strncmp(env->str, "PATH=", 5) != 0)
		env = env->next;
	paths = ft_split(env->str + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmdpath, X_OK) == 0)
		{
			free_array(paths);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	i = 0;
	free_array(paths);
	return (NULL);
}

int	ft_listsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


char	**env_to_array(t_env *env)
{
	char	**envarray;
	int		len;
	int		i;

	i = 0;
	len = ft_listsize(env);
	envarray = malloc((len + 1) * sizeof(char *));
	while (env)
	{
		envarray[i] = strdup(env->str);
		i++;
		env = env->next;
	}
	envarray[i] = NULL;
	return (envarray);
}

void	exec_cmd(t_data *data)
{
	char	*path;
	char 	**envarray;

	if (access(data->cmd[0], X_OK) == 0)
		path = data->cmd[0];
	else
	{
		path = get_path(data->cmd[0], data->env);
		if (!path)
		{
			printf("path error\n");
			return ;
		}
	}
	envarray = env_to_array(data->env);
	execve(path, data->cmd, envarray);
	free_array(envarray);
	printf("execve error\n");
}