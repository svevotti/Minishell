/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:17:16 by joschka           #+#    #+#             */
/*   Updated: 2024/03/20 14:24:20 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirect(t_proc *proc)
{
	if (proc->fd_in)
	{
		dup2(proc->fd_in, STDIN_FILENO);
		close(proc->fd_in);
	}
	if (proc->fd_out)
	{
		dup2(proc->fd_out, STDOUT_FILENO);
		close(proc->fd_out);
	}
}

int	open_outfile(t_proc *proc, int type)
{
	if (proc->fd_out)
		close(proc->fd_out);
	if (type == TRUNC_OUTFILE)
		proc->fd_out = open(proc->outfile, O_WRONLY
				| O_CREAT | O_TRUNC, 0777);
	if (type == APPEND_OUTFILE)
		proc->fd_out = open(proc->outfile, O_WRONLY
				| O_CREAT | O_APPEND, 0777);
	if (proc->fd_out == -1)
	{
		proc->fd_out = 0;
		ft_error(proc->outfile, 0);
		return (1);
	}
	return (0);
}

int	open_file(t_proc *proc, int type)
{
	if (type == TRUNC_OUTFILE || type == APPEND_OUTFILE)
	{
		if (open_outfile(proc, type))
			return (1);
	}
	else if (type == INFILE)
	{
		if (proc->fd_in)
			close(proc->fd_in);
		proc->fd_in = open(proc->infile, O_RDONLY, 0777);
		if (proc->fd_in == -1)
		{
			proc->fd_in = 0;
			ft_error(proc->infile, 0);
			return (1);
		}
	}
	return (0);
}

void	get_filename(t_proc *proc, char *file, int type)
{
	if (type <= APPEND_OUTFILE)
	{
		if (!proc->outfile)
			proc->outfile = ft_strdup(file);
		else
		{
			free(proc->outfile);
			proc->outfile = ft_strdup(file);
		}
	}
	if (type == INFILE)
	{
		if (!proc->infile)
			proc->infile = ft_strdup(file);
		else
		{
			free(proc->infile);
			proc->infile = ft_strdup(file);
		}
	}
}

void	prepare_redirection(t_proc *proc, char *redirection, char *file_name)
{
	int	type;
	int	ret;

	ret = 0;
	if (proc->no_exec)
		return ;
	type = is_redirection(redirection);
	if (type <= INFILE)
	{
		get_filename(proc, file_name, type);
		ret = open_file(proc, type);
	}
	else if (type == HEREDOC)
	{
		ret = get_heredoc(proc, file_name);
	}
	proc->no_exec = ret;
}
