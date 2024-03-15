/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:21:35 by jbeck             #+#    #+#             */
/*   Updated: 2024/03/15 11:48:15 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_proc	*init_cmd(int id)
{
	t_proc	*cmd;

	cmd = malloc(sizeof(t_proc));
	if (!cmd)
		return (NULL);
	cmd->id = id;
	cmd->path = NULL;
	cmd->cmdlist = NULL;
	cmd->cmd = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->pipe_in = -1;
	cmd->pipe_out = -1;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->no_exec = 0;
	return (cmd);
}

void	list_to_array(t_proc *proc)
{
	int		len;
	int		i;
	t_list	*run;

	i = 0;
	len = ft_lstsize(proc->cmdlist);
	proc->cmd = malloc((len + 1) * sizeof(char *));
	run = proc->cmdlist;
	while (run)
	{
		proc->cmd[i] = ft_strdup(run->content);
		i++;
		run = run->next;
	}
	proc->cmd[i] = NULL;
}

void	create_cmd_list(t_data *data)
{
	int		i;
	int		id;

	i = 0;
	id = 1;
	data->procs = ft_lstnew(init_cmd(id));
	while (data->input[i])
	{
		if (data->input[i][0] == '|')
		{
			id++;
			ft_lstadd_back(&data->procs, ft_lstnew(init_cmd(id)));
		}
		i++;
	}
}

void	fill_cmd_nodes(t_list *procs, t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (is_redirection(data->input[i]))
		{
			prepare_redirection(procs->content, data->input, i);
			i += 2;
		}
		else if (!ft_strcmp(data->input[i], "|"))
		{
			i++;
			procs = procs->next;
		}
		else
		{
			ft_lstadd_back(&((t_proc *)procs->content)->cmdlist,
				ft_lstnew(data->input[i]));
			i++;
		}
	}
}

void	parse_cmds(t_data *data)
{
	t_list	*run;

	create_cmd_list(data);
	fill_cmd_nodes(data->procs, data);
	run = data->procs;
	while (run)
	{
		list_to_array(run->content);
		run = run->next;
	}
}
