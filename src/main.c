#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>


#define	ERROR_1PIPE 1
#define ERROR_2PLUSPIPE 2
#define ERROR_1REDIRECTION_INPUT 3
#define ERROR_2REDIRECTION_INPUT 4
#define ERROR_3REDIRECTION_INPUT 5
#define ERROR_4PLUSREDIRECTION_INPUT 6
#define ERROR_1REDIRECTION_OUTPUT 7
#define ERROR_2REDIRECTION_OUTPUT 8
#define ERROR_3REDIRECTION_OUTPUT 9
#define ERROR_4REDIRECTION_OUTPUT 10
#define ERROR_5PLUSREDIRECTION_OUTPUT 11


void	initialize_env(char **argv, char argc, t_data *data, char **envp);
char	**get_split_input(char *str, t_data *data);
int		child_process(char **input, t_env *env, char **envp);

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);
}
void	print_error_token(int check)
{
	if (check == ERROR_1PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (check == ERROR_2PLUSPIPE)
		printf("bash: syntax error near unexpected token `||'\n");
	else if (check == ERROR_1REDIRECTION_INPUT || check == ERROR_2REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (check == ERROR_3REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (check == ERROR_4PLUSREDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (check == ERROR_1REDIRECTION_OUTPUT || check == ERROR_2REDIRECTION_OUTPUT || check == ERROR_3REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (check == ERROR_4REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (check == ERROR_5PLUSREDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<<'\n");
}

#define ERROR -1
#define FREE -1
#define	PIPE_END -2

 #include <string.h>
int	check_first_argv(char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '|')
		{
			while (*str == '|')
			{
				count++;
				str++;
			}
			break ;
		}
		str++;
	}
	if (count >= 1)
	{
		if (count == 1)
			print_error_token(ERROR_1PIPE);
		else
			print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}

int	check_tokens_error(char **input)
{
	int i;
	char	*box;
	int		count;

	i = 0;
	count = 0;
	if (check_first_argv(input[i]) == ERROR)
		return (ERROR);
	while (input[i] != NULL)
	{
		box = input[i];
		while (*box != '\0')
		{
			if (*box == '|')
			{
				while (*box == '|')
				{
					count++;
					box++;
				}
				break ;
			}
			box++;
		}
		i++;
	}
	if (count > 1)
	{
		print_error_token(ERROR_2PLUSPIPE);
		return (ERROR);
	}
	return (0);
}

int	find_size_input_array(char **array)
{
	int	i;

	i = 0;
	while (*array != NULL)
	{
		array++;
		i++;
	}
	return (i);
}

int	check_pipe(char *str)
{
	int	size;

	size = ft_strlen(str);
	str += size - 1;
	if (*str == '|')
		return (1);
	return (0);
}

int	check_pipe_end(char **input)
{
	int	size_array;
	
	size_array = find_size_input_array(input);
	if (check_pipe(input[size_array - 1]) == 1)
		return(PIPE_END);
	return (0);
}

int	find_size_pipe_end(char *str)
{
	int	new_pipe;
	int	count;
	char	*prompt;

	new_pipe = 1;
	count = 0;
	while (new_pipe == 1)
	{
		new_pipe = 0;
		count++;
		if (strcmp(str, "|") == 0)
		{
			prompt = readline("size∙ ");
			int	size_prompt = ft_strlen(prompt);
			prompt += size_prompt - 1;
			while (*prompt == ' ' || *prompt == '\n' || *prompt == '\t')
				prompt--;
			if (*prompt == '|')
				new_pipe = 1;		
		}
	}
	return (count);
}

void *get_cmd_pipes(int)
{
	int		new_pipe;
	char	*prompt;
	int		*size_array;
	char	*array_pipes;

	new_pipe = 1;
	while (new_pipe == 1)
	{
		new_pipe = 0;
		prompt = readline("str∙ ");
		int	size_prompt = ft_strlen(prompt);
		prompt += size_prompt - 1;
		while (*prompt == ' ' || *prompt == '\n' || *prompt == '\t')
			prompt--;
		if (*prompt == '|')
			new_pipe = 1;
	}
	exit(6);
	return (NULL);
}

void	update_input(char **input)
{
	int	size_input;
	int	size_new_input;
	char	**new_input;
	char	*str_new_pipes;
	char	*str;


	size_input = find_size_input_array(input);
	size_new_input = find_size_pipe_end(input[size_input - 1] + size_input);
	new_input = (char **)malloc(sizeof(char *) * (size_new_input + 1));
	get_cmd_pipes(find_size_pipe_end(input[size_input - 1]));
	//new_input[i] = NULL;

	// get_cmd = input[size_input - 1];
	// int count = 0;
	// while (new_pipe == 1)
	// {
	// 	new_pipe = 0;
	// 	count++;
	// 	if (strcmp(get_cmd, "|") == 0)
	// 	{
	// 		prompt = readline("~");
	// 		temp = prompt;
	// 		int	size_prompt = ft_strlen(prompt);
	// 		temp += size_prompt - 1;
	// 		while (*temp == ' ' || *temp == '\n' || *temp == '\t')
	// 			temp--;
	// 		if (*temp == '|')
	// 			new_pipe = 1;
	// 	}
	// }
	// printf("count pipes in prompt %d\n", count);
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
		if (check_pipe_end(split_input) == PIPE_END)
		{
			printf("size array %d\n", find_size_input_array(split_input));
			update_input(split_input);
			exit(1);

			
		}
		if (check_tokens_error(split_input) == ERROR)
		{
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
