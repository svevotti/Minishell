/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:40:16 by joschka           #+#    #+#             */
/*   Updated: 2024/03/01 18:08:11 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	just_for_norm(void)
{
	perror("fork");
	return (1);
}

int	run_executor(t_data *data)
{
	int		status;
	int		exitcode;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (just_for_norm());
	if (pid == 0)
	{
		status = executor(data, data->procs);
		if (!data->procs->next)
		{
			free_data(data);
			exit(status);
		}
		free_data(data);
	}
	else
		wait(&status);
	if (WIFEXITED(status))
		exitcode = WEXITSTATUS(status);
	return (exitcode);
}

int	minishell(t_data *data)
{
	int	exitcode;

	data->procs = NULL;
	if (parse_cmds(data))
		return (1);
	if (is_builtin(data->procs->content) && !data->procs->next)
	{
		redirect(data->procs->content);
		exitcode = exec_builtin(data->procs->content);
	}
	else
		exitcode = run_executor(data);
	return (exitcode);
}
