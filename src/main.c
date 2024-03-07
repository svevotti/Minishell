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

char	*find_cmd(char *str)
{
	char *cmd;
	char *temp;
	int len;
	int i;

	i = 0;
	temp = str;
	len = 0;
	i = 0;
	while (*temp != '\0')
	{
		if (*temp == ' ' || *temp == '\n' || *temp == '\t')
			break;
		temp++;
		len++;
	}
	cmd = (char *)malloc(sizeof(char) * (len + 1));
	if (cmd == NULL)
		return (NULL);
	temp = cmd;
	while (i < len)
	{
		*temp++ = *str++;
		i++;
	}
	*temp = '\0';
	return (cmd);
}

int	check_cmd(char *str)
{
	char *cmd;
	
	cmd = find_cmd(str);
	if (cmd == NULL)
		return (1);
	return (0);
}

int	check_syntax(char *str)
{
	char	*cmd;
	char	*temp;

	while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	cmd = find_cmd(str);
	temp = cmd;
	int count = 0;
	if (*temp == '|')
	{
		while (*temp == '|')
			{
				count++;
				temp++;
			}
	}
	if (*temp == '>')
	{
		while (*temp == '>')
		{
			printf("here\n");
			count++;
			temp++;
		}
	}
	else if (*temp == '<')
	{
		while (*temp != '<')
		{
			count++;
			temp++;
		}
	}
	if (*cmd == '|')
	{
		if (count == 1)
			return (ERROR_1PIPE);
		else
			return (ERROR_2PLUSPIPE);
	}
	else if (*cmd == '>')
	{
		if (count == 1 && ft_strlen(str) == 1)
			return (ERROR_1REDIRECTION_INPUT);
		else if (count == 2 && ft_strlen(str) == 2)
			return (ERROR_2REDIRECTION_INPUT);
		else if (count == 3)
			return (ERROR_3REDIRECTION_INPUT);
		else if (count > 3)
			return (ERROR_4PLUSREDIRECTION_INPUT);
	}
	else if (*cmd == '<')
	{
		if (count == 1 && ft_strlen(str) == 1)
			return (ERROR_1REDIRECTION_OUTPUT);
		else if (count == 2 && ft_strlen(str) == 2)
			return (ERROR_2REDIRECTION_OUTPUT);
		else if (count == 3)
			return (ERROR_3REDIRECTION_OUTPUT);
		else if (count == 4)
			return (ERROR_4REDIRECTION_OUTPUT);
		else if (count > 4)
			return (ERROR_5PLUSREDIRECTION_OUTPUT);
	}
	return (0);
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

int	get_flag_exec(char *str)
{
	int check;
	int flag = 0;

	flag = 0;
	check = check_syntax(str);
	if (check != 0)
	{
		flag = 1;
		print_error_token(check);
	}
	return (flag);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data	data;
	int		exitcode;
	int		flag;
	char	**split_input;

	initialize_env(argv, argc, &data, envp);
	signal(SIGINT, sighandler);
	while (1)
	{
		flag = 0;
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		add_history(line);
		split_input = get_split_input(line, &data);
		if (split_input == NULL)
			return (1);
		flag = get_flag_exec(line);
		if (flag == 0) {
			data.input = get_split_input(line, &data);
			if (data.input)
			{
				exitcode = minishell(&data);
				printf("exitcode main: %d\n", exitcode);
				free_procs(data.procs);
				free_array(data.input); 
			}
		}
		free(line);
	}
	return (0);
}

int	find_len_input(char **input)
{
	int	count;

	count = 0;
	while (*input != NULL)
	{
		count++;
		input++;
	}
	return (count);
}

int	get_tokens(char *str)
{
	int	count;
	char *temp;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '|')
		{
			temp = str;
			temp++;
			if (*temp == '|')
				count--;
			count++;
		}
		str++;
	}
	return (count);
}

int	count_tokens(char **input, int size)
{
	int count;
	int	i;
	
	i = 0;
	count = 0;
	while (i < size)
	{
		if (ft_strlen(input[i]) > 1)
			count = get_tokens(input[i]) + count;
		i++;
	}
	return (count);
}

char	**add_tokens(char **input)
{
	char	**new_input;
	int		size_new_input;
	int		num_tokens;
	int		size_input;

	size_input = find_len_input(input);
	num_tokens = count_tokens(input, size_input);
	size_new_input = size_input + num_tokens;
	new_input = (char **)malloc(sizeof(char *) * (size_new_input) + 1);
	if (new_input == NULL)
		return (NULL);
	printf("size new input %d from input %d and tokens %D\n", size_new_input, size_input, num_tokens);




	return (NULL);
}

#define	ERROR_1ARGV -1
#define	ERROR_OR -2

int	get_num_pipes(char *input)
{
	int	count;
	int	flag;
	char	*temp;

	flag = 0;
	count = 0;
	while (*input != '\0')
	{
		if (*input == '|')
		{
			if (flag == 0)
			{
				temp = input;
				temp++;
				if (*temp != '|')
					return (ERROR_1ARGV);
				else
					return (ERROR_OR);
			}
			else
			{
				temp = input;
				temp++;
				if (*temp == '|')
					return (ERROR_OR);
				count++;
			}
		}
		flag = 1;
		input++;
	}
	return (count);
}

int	check_pipe_end(char *str)
{
	int	flag;
	int	size;

	size = ft_strlen(str);
	str += size - 1;
	flag = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t')
			str--;
	
	while (size > 0)
	{
		if (*str == '|')
			flag = 1;
		str--;
		size--;
	}
	return (flag);
}

char	**split_by_pipes(char *input)
{
	int	number_processes;
	int	flag_pipe_end;
	char	**get_processes;

	number_processes = get_num_pipes(input);
	if (number_processes < 0)
	{
		// print_error(number_processes);
		// free(input);
		return (NULL);
	}
	else
		number_processes++;
	flag_pipe_end = check_pipe_end(input);
	get_processes = (char **)malloc(sizeof(char *) * (number_processes + 1));
	if (get_processes == NULL)
	{
		free(input);
		return (NULL);
	}

	// exit(1);
	return (NULL);
}
char	**get_split_input(char *str, t_data *data)
{
	char		*expanded_input;
	char		**split_input;
	char		**split_input_pipes;

	expanded_input = expand_input(str, data);
	if (expanded_input == NULL)
		return (NULL);
	split_input_pipes = split_by_pipes(expanded_input);
	if (split_input_pipes == NULL)
		return (NULL);
	split_input = split_function(expanded_input);
	if (split_input == NULL)
	{
		free_strings(str, expanded_input, NULL);
		return (NULL);
	}
	// split_by_tokens = add_tokens(split_input);
	// exit(1);
	// if(split_by_tokens == NULL)
	// {
	// 	free_strings(str, expanded_input, split_input);
	// 	return (NULL);
	// }
	return (split_input);
}

void	initialize_env(char **argv, char argc, t_data *data, char **envp)
{
	(void)argc;
	(void)argv;
	trans_env(data, envp);
}
