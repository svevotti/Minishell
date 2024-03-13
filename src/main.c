#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#define ERROR -1

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

void	free_strs(char *str, char **array)
{
	int	i;

	i = 0;
	free(str);
	if (array != NULL)
		free_array(array);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	char	**split_input;
	// int		exitcode;

	initialize_signals();
	initialize_env(argv, argc, &data, envp);
	if (argc > 1)
		exit(1);
	while (1)
	{
		line = readline("(=^･^=) ");
		if (check_endoffile(line) == -1)
		{
			free(line);
			exit(55);
		} //ctrl D is EOF
		add_history(line);
		split_input = get_split_input(line, &data);
		if (split_input == NULL)
		{
			free_strs(line, NULL);
			return (1);
		}
		if (find_size_input_array(split_input) == 0)
			continue ;
		if (tokens_error(split_input) == ERROR)
		{
			printf("add line %p, add split input %p\n", line, split_input);
			free_strs(line, NULL);
		}
		else
		{
			data.input = split_input;
			if (data.input)
			{
				minishell(&data);
				free_procs(data.procs);
				free_array(data.input);
				free(line);
			}
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
		//free_strings(str, expanded_input, NULL);
		return (NULL);
	}
	free(expanded_input);
	return (split_input);
}
