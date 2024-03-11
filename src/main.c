#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#define ERROR -1

void	initialize_env(char **argv, char argc, t_data *data, char **envp);
char	**get_split_input(char *str, t_data *data);
int		child_process(char **input, t_env *env, char **envp);

void sighandler(int signum) {

	(void)signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data	data;
	char	**split_input;

	initialize_env(argv, argc, &data, envp);
	signal(SIGINT, sighandler);
	while (1)
	{
		line = readline("(=^･^=) ");
		add_history(line);
		split_input = get_split_input(line, &data);
		if (split_input == NULL)
			return (1);
		if (find_size_input_array(split_input) == 0)
			continue ;
		// printf("array - ");
		// print_array(split_input);
		if (tokens_error(split_input) == ERROR)
		{
			//return(55);
			//free stuff
			//return (1);
		}
		else
		{
			data.input = split_input;
			if (data.input)
			{
				minishell(&data);
				free_procs(data.procs);
				free_array(data.input); 
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
		free_strings(str, expanded_input, NULL);
		return (NULL);
	}
	return (split_input);
}

void	initialize_env(char **argv, char argc, t_data *data, char **envp)
{
	(void)argc;
	(void)argv;
	trans_env(data, envp);
}
