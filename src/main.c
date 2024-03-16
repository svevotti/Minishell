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

void	initialize_env(char **argv, char argc, t_data *data, char **envp);
char	**get_split_input(char *str, t_data *data);
int		child_process(char **input, t_env *env, char **envp);

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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

int	find_size_pipe(char *str)
{
	int	count;
	int	single_quote;
	int	double_quote;
	int	pipe_number;

	count = 1;
	single_quote = 0;
	double_quote = 0;
	char *temp;
	temp = str + ft_strlen(str) - 1;
	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	if (*str == '|')
	{
		pipe_number = 0;
		while (*str == '|')
		{
			pipe_number++;
			str++;
		}
		if (pipe_number == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	if (*temp == '|')
	{
		pipe_number = 0;
		while (*temp == '|')
		{
			pipe_number++;
			temp--;;
		}
		if (pipe_number == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	while (*str != '\0')
	{
		pipe_number = 0;
		if (*str == 34 || *str == 39)
		{
			if (*str == 39)
			{
				if (single_quote == 0)
					single_quote = 1;
				else
					single_quote = 0;
			}
			else if (*str == 34)
			{
				if (double_quote == 0)
					double_quote = 1;
				else
					double_quote = 0;
			}
		}
		else if (*str == '|' && single_quote == 0 && double_quote == 0)
		{
			count++;
			while (*str == '|')
			{
				pipe_number++;
				str++;
			}
			if (pipe_number > 1)
			{
				if (pipe_number == 1)
					print_error_token(ERROR_1PIPE);
				else
					print_error_token(ERROR_2PLUSPIPE);
				return (ERROR);
			}
		}
		str++;
	}
	return (count);
}

int	count_len_process(char *str)
{
	int	count;
	int	single_quote;
	int	double_quotes;

	count = 0;
	single_quote = 0;
	double_quotes = 0;
	//---echo----$HOME--
	while (*str != '\0')
	{
		if (*str == '|' && single_quote == 0 && double_quotes == 0)
			break ;
		else if (*str == 39)
		{
			if (double_quotes == 0)
				single_quote = get_quote_flag(single_quote);
			else
				count++;
		}
		else if (*str == 34)
		{
			if (single_quote == 0)
				double_quotes = get_quote_flag(double_quotes);
			else
				count++;
		}
		else
			count++;
		str++;
	}
	return (count);
}

char	*get_process(char *str, t_data *data)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;
	int	single_quote;
	int	double_quotes;

	(void)data;
	single_quote = 0;
	double_quotes = 0;
	size_string = count_len_process(str);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		if (*str == 39 || *str == 34)
		{
			if (*str == 39)
			{
				if (single_quote == 0)
					single_quote = 1;
				if (double_quotes == 0)
					str++;
				else
				{
					*temp++ = *str++;
					count++;
				}
			}
			else if (*str == 34)
			{
				if (double_quotes == 0)
					double_quotes = 1;
				if (single_quote == 0)
					str++;
				else
				{
					*temp++ = *str++;
					count++;
				}
			}
		}
		else
		{
			*temp++ = *str++;
			count++;
		}
	}
	*temp = '\0';
	return (single_str);
}

char **split_pipes(char *str, t_data *data)
{
	char	**array_processes;
	int		array_size;
	char	*process;
	// int		process_size;
	int		i;

	i = 0;
	(void)data;
	array_size = find_size_pipe(str);
	printf("size %d\n", array_size);
	if (array_size == ERROR)
		return (NULL);
	array_processes = (char **)malloc(sizeof(char *) * (array_size + 1));
	if (array_processes == NULL)
		return (NULL);
	while (i < array_size)
	{
		process = get_process(str, data);
		if (process == NULL)
			return (NULL);
		str += ft_strlen(process) + 1;
		printf("process %s, index %d - str %s\n", process, i, str);
		array_processes[i] = process;
		i++;
	}
	array_processes[i] = NULL;
	return (array_processes);
}

void print_array(char **str)
{
	int i = 0;
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char	**get_split_input(char *str, t_data *data)
{
	char		*expanded_input;
	char		**split_input;
	char 		**array_processes;

	expanded_input = expand_input(str, data);
	if (expanded_input == NULL)
		return (NULL);
	array_processes = split_pipes(expanded_input, data);
	print_array(array_processes);
	exit(100);	
	split_input = split_function(expanded_input, data);
	if (split_input == NULL)
	{
		free(expanded_input);
		return (NULL);
	}
	free(expanded_input);
	return (split_input);
}
