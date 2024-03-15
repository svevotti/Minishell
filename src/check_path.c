/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:28:41 by jbeck             #+#    #+#             */
/*   Updated: 2024/03/15 16:34:20 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_path_error(char *arg, int flag)
{
	char	*str;

	if (flag == 1)
	{
		str = ft_strjoin(arg, ": command not found\n");
		ft_print_error(str, 2);
	}
	if (flag == 2)
	{
		str = ft_strjoin(arg, ": Is a directory\n");
		ft_print_error(str, 2);
	}
	if (flag == 3)
	{
		str = ft_strjoin(arg, ": Permission denied\n");
		ft_print_error(str, 2);
	}
	if (flag == 4)
	{
		str = ft_strjoin(arg, ": No such file or directory\n");
		ft_print_error(str, 2);
	}
	free(str);
}

void	path_error(t_data *data, t_proc *proc, int flag)
{
	usleep(50000);
	ft_path_error(proc->path, flag);
	free(proc->path);
	free_data(data);
	if (flag == 1 || flag == 4)
		exit(127);
	if (flag == 2 || flag == 3)
		exit(126);
}

void	check_for_access(t_data *data, t_proc *proc)
{
	struct stat	sb;

	if (access(proc->path, X_OK) == -1)
	{
		if (errno == EACCES)
			path_error(data, proc, 3);
		else
			path_error(data, proc, 1);
	}
	if (stat(proc->path, &sb) == 0)
	{
		if ((sb.st_mode & S_IFMT) != S_IFREG)
			path_error(data, proc, 1);
	}
}

void	precheck_path(t_data *data, t_proc *proc)
{
	struct stat	sb;

	if (access(proc->cmd[0], F_OK) != 0)
		proc->path = get_path(proc->cmd[0], data->env);
	if (proc->path == NULL)
		proc->path = ft_strdup(proc->cmd[0]);
	if (proc->path[0] == '/' || proc->path[0] == '.')
	{
		if (stat(proc->path, &sb) == -1)
		{
			if (errno == ENOENT)
				path_error(data, proc, 4);
			else if (errno == EACCES)
				path_error(data, proc, 3);
			else
				perror("stat");
		}
		if (S_ISDIR(sb.st_mode))
			path_error(data, proc, 2);
	}
	check_for_access(data, proc);
}
