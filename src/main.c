/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:02 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 18:10:10 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig;

// todo: whitespaces, change getenv to check size of our env var,
// (=^･^=) "$test"
// /usr/local/sbin/: Is a directory
// $? invalid read of size 1
// check number of quotes = even


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

	int single_quote = 0;
	int double_quote = 0;
	line = readline("(=^･^=) ");
	check_for_signal(data);
	if (line == NULL)
	{
		free_env(data->env);
		exit(data->exitcode);
	}
	add_history(line);
	char *temp;
	temp = line;
	while (*temp != '\0')
	{
		if (*temp == 34)
			get_flag(&single_quote, &double_quote, *temp);
		else if (*temp == 39)
			get_flag(&single_quote, &double_quote, *temp);
		temp++;
	}
	if (single_quote != 0 || double_quote != 0)
	{
		free(line);
		return (ERROR);
	}
	if (ft_strlen(line) > 0)
	{
		if (get_split_input(line, data) == -1)
		{
			free_array(data->input);
			data->input = NULL;
			free(line);
			return (ERROR);
		}
	}
	else
		return (EMPTY);
	free(line);
	return (SUCCESS);
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
	{
		free(expanded_input);
		return (ERROR);
	}
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
