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
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
}

int	check_endoffile(char *str)
{
	if (str == NULL)
		return (-1);
	return (0);
}

void	free_strs(char *str, char **array, t_env *env)
{
	free(str);
	free_env(env);
	if (array != NULL)
		free_array(array);
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
		if (tokens_error(data->input) == ERROR)
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

		}
	}
	return (0);
}

char	**get_split_input(char *str, t_data *data)
{
	char		*expanded_input;
	char		**split_input;

	expanded_input = expand_input(str, data);
	if (expanded_input == NULL)
		return (NULL);
	split_input = split_function(expanded_input);
	if (split_input == NULL)
	{
		free(expanded_input);
		return (NULL);
	}
	free(expanded_input);
	return (split_input);
}
