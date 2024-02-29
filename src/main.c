#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>

void print_array(char **str)
{
	int i = 0;
	
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	char static *line;
	char		*expanded_input;
	t_data		data;
  	char     **split_input;
	pid_t	id_child;
	int		status;

	(void)argc;
	(void)argv;
	trans_env(&data, envp);
	data.env->exit_status = 0;
	while (1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		add_history(line);
		expanded_input = expand_input(line, &data);
		split_input = split_function(expanded_input);
		id_child = fork();
		if (id_child == 0)
			execute_cmd(split_input, data.env, envp);
		else if (id_child < 0)
			printf("error id\n");
		else
		{
			wait(&status);
			int status_code = WEXITSTATUS(status);
			data.env->exit_status = status_code;
		}
		free(line);
	}
	return (0);
}
