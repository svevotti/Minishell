/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:02 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:35:03 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

char	**get_split_input(char *str, t_data *data);
void	get_input(t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	initialize(argv, argc, &data, envp);
	while (1)
	{
		get_input(&data);
		if (data.input)
		{
			data.exitcode = minishell(&data);
			free_procs(data.procs);
			free_array(data.input);
			data.input = NULL;
		}
	}
	return (0);
}

void	get_input(t_data *data)
{
	char	*line;

	line = readline("(=^･^=) ");
	if (!line)
	{
		free_env(data->env);
		exit(data->exitcode);
	}
	add_history(line);
	if (ft_strlen(line))
		data->input = get_split_input(line, data);
	if (data->input)
	{
		if (check_redirections(data->input) == ERROR)
		{
			free_array(data->input);
			data->input = NULL;
			data->exitcode = 2;
		}
	}
	free(line);
}

char	**get_split_input(char *str, t_data *data)
{
	char		*expanded_input;
	char 		**array_processes;

	expanded_input = expand_input(str, data);
	if (expanded_input == NULL)
		return (NULL);
	array_processes = split_pipes(expanded_input, data);
	//print_array(array_processes);
	if (array_processes == NULL)
		return (NULL);
	get_array_pipes(array_processes, data);
	// print_3d_array(array_tokens);
	free(expanded_input);
	return (NULL);
}
