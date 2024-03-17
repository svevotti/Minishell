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

int	count_words_process(char *str)
{
	int count;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	while (*str != '\0')
	{
		count++;
		str = traverse_token(str);
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	}
	return (count);
}

char	***split_words(char **processes, t_data *data)
{
	char	***array_tokens;
	int		nbr_words;
	int		size_array_tokens;
	int		i;
	int		j;

	(void)data;
	size_array_tokens = find_size_input_array(processes);
	array_tokens = (char ***)malloc(sizeof(char **) * (size_array_tokens) + 1);
	if (array_tokens == NULL)
		return (NULL);
	i = 0;
	j = 0;
	//printf("array size %d\n", size_array_tokens);
	while (i < size_array_tokens)
	{
		nbr_words = count_words_process(processes[i]);
		//printf("%i ~ nbr words %d\n", i, nbr_words);
		i++;
	}
	return (NULL);
}
char	**get_split_input(char *str, t_data *data)
{
	char		*expanded_input;
	char		**split_input;
	char 		**array_processes;
	char 		***array_words;

	expanded_input = expand_input(str, data);
	if (expanded_input == NULL)
		return (NULL);
	array_processes = split_pipes(expanded_input, data);
	printf("arrat processes 1 ~ ");
	print_array(array_processes);
	if (array_processes == NULL)
		return (NULL);
	array_words = split_words(array_processes, data);
	// exit(100);	
	split_input = split_function(expanded_input, data);
	if (split_input == NULL)
	{
		free(expanded_input);
		return (NULL);
	}
	free(expanded_input);
	return (split_input);
}
