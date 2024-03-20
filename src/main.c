/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:02 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 11:54:44 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

#define SUCCESS 0
#define EMPTY 1
int	g_sig;

int	get_split_input(char *str, t_data *data);
int	get_input(t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	initialize(argv, argc, &data, envp);
	while (1)
	{
		if (pipe(data.exit_fd) == -1)
			perror("pipe");
		handle_signals_main();
		if (get_input(&data) == SUCCESS)
			data.exitcode = minishell(&data);
		free_procs(data.procs);
		data.procs = NULL;
		free_array(data.input);
		data.input = NULL;
		close(data.exit_fd[1]);
		read(data.exit_fd[0], &data.exitcode, sizeof(int));
		close(data.exit_fd[0]);
	}
	return (0);
}

int	get_input(t_data *data)
{
	char	*line;

	line = readline("(=^･^=) ");
	check_for_signal(data);
	if (!line)
	{
		free_env(data->env);
		exit(data->exitcode);
	}
	add_history(line);
	if (ft_strlen(line) > 0)
	{
		if (get_split_input(line, data) == -1)
		{
			free_array(data->input);
			data->input = NULL;
			return (ERROR);
		}
	}
	else
		return (EMPTY);
	free(line);
	return (0);
}

int	get_split_input(char *str, t_data *data)
{
	char	*expanded_input;
	char	**array_processes;

	expanded_input = expand_input(str, data);
	if (expanded_input == NULL)
		return (ERROR);
	array_processes = split_pipes(expanded_input, data);
	if (array_processes == NULL)
		return (ERROR);
	if (get_array_pipes(array_processes, data) == -1)
	{
		free_array(array_processes);
		free(expanded_input);
		return (ERROR);
	}
	free_array(array_processes);
	free(expanded_input);
	return (0);
}
