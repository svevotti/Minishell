/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:12:02 by joschka           #+#    #+#             */
/*   Updated: 2024/03/02 13:46:42 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_pipe(pid_t pid, t_proc *proc, int *fd)
{
	if (pid == 0)
	{
		close(fd[1]);
		proc->pipe_out = dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		return (0);
	}
	else
	{
		close(fd[0]);
		proc->pipe_in = dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		return (2);
	}
}

int	pipe_and_fork(t_proc *proc)
{
	int		fd[2];
	int		ret;
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (3);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (4);
	}
	ret = redirect_pipe(pid, proc, fd);
	return (ret);
}

int	childproc(t_data *data, t_list *proc)
{
	int	ret;

	ret = executor(data, proc->next);
	free_data(data);
	return (ret);
}

int	parentproc(t_data *data, t_list *proc, int parent)
{
	int	ret;
	int	wstatus;

	redirect(proc->content);
	ret = exec_cmd(data, proc->content, data->env);
	if (parent == 2)
	{
		if (((t_proc *)proc->content)->pipe_in > -1)
			close(((t_proc *)proc->content)->pipe_in);
		wait(&wstatus);
		if (WIFEXITED(wstatus))
			ret = WEXITSTATUS(wstatus);
		free_data(data);
		exit(ret);
	}
	return (ret);
}

int	executor(t_data *data, t_list *proc)
{
	int		parent;
	int		ret;

	parent = 1;
	ret = -1;
	if (proc->next)
		parent = pipe_and_fork(proc->content);
	if (!parent)
	{
		ret = childproc(data, proc);
		exit(ret);
	}
	if (parent)
	{
		ret = parentproc(data, proc, parent);
	}
	return (ret);
}
