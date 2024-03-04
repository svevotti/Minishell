#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>

void	initialize_env(char **argv, char argc, t_data *data, char **envp);
char	**get_split_input(char *str, t_data *data);
int		child_process(char **input, t_env *env, char **envp);

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data		data;
	char		**split_input;

	initialize_env(argv, argc, &data, envp);
	while (1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		add_history(line);
		split_input = get_split_input(line, &data);
		//store split in struct t_data
		//call minishell
		if (split_input == NULL)
		{
			if (data.flag == 1)
			{
				free(line);
				return (1);
			}
			printf("\n");
		}
		if (child_process(split_input, data.env, envp) < 0)
		{
			free_strings(line, NULL, split_input);
			return (1);
		}
		free(line);
	}
	return (0);
}

char	**get_split_input(char *str, t_data *data)
{
	char		*expanded_input;
	char		**split_input;

	expanded_input = expand_input(str, data);
	if (expanded_input == NULL)
	{
		if (data->flag == 1)
			free_strings(str, NULL, NULL);
		return (NULL);
	}
	split_input = split_function(expanded_input);
	if (split_input == NULL)
	{
		free_strings(str, expanded_input, NULL);
		return (NULL);
	}
	return (split_input);
}

int	child_process(char **input, t_env *env, char **envp)
{
	pid_t		id_child;
	int			status;
	int			status_code;

	id_child = fork();
	if (id_child == 0)
		execute_cmd(input, env, envp);
	else if (id_child < 0)
	{
		perror("error\n");
		return (id_child);
	}
	else
	{
		wait(&status);
		status_code = WEXITSTATUS(status);
		env->exit_status = status_code;
	}
	return (id_child);
}

void	initialize_env(char **argv, char argc, t_data *data, char **envp)
{
	(void)argc;
	(void)argv;
	trans_env(data, envp);
	data->env->exit_status = 0;
	data->flag = 0;
}
