/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:40:16 by joschka           #+#    #+#             */
/*   Updated: 2024/03/14 15:56:59 by jbeck            ###   ########.fr       */
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
	exitcode = WEXITSTATUS(status);
	return (exitcode);
}

void	restore_std(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}

int	minishell(t_data *data)
{
	int	exitcode;
	t_list *list;

	list = data->procs;
	printf("-----before execution\n");
	print_proc_items(list);
	if (is_builtin(data->procs->content) && !data->procs->next)
	{
		data->exit = 1;
		redirect(data->procs->content);
		exitcode = exec_builtin(data->procs->content, data);
		data->exit = 0;
	}
	else
		exitcode = run_executor(data);
	restore_std(data->std_in, data->std_out);
	// printf("-----after execution\n");
	// print_proc_items(list);
	return (exitcode);
}
