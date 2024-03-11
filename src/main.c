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
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data	data;
	int		exitcode;
	char	**split_input;
	// char	**new_input;

	initialize_env(argv, argc, &data, envp);
	signal(SIGINT, sighandler);
	while (1)
	{
		line = readline("(=^･^=) ");
		add_history(line);
		split_input = get_split_input(line, &data);
		if (split_input == NULL)
			return (1);
		// printf("array - ");
		// print_array(split_input);
		// if (check_pipe_end(split_input) == PIPE_END)
		// {
		// 	printf("size array %d\n", find_size_input_array(split_input));
		// 	update_input(split_input);
		// 	exit(1);

			
		// }
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
				exitcode = minishell(&data);
				printf("exitcode main: %d\n", exitcode);
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
