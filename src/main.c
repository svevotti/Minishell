#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>


#define REDIRECTION_INPUT 1
#define DOUBLE_REDIRECTION_INPUT 2
#define REDIRECTION_OUTPUT 3
#define DOUBLE_REDIRECTION_OUTPUT 4
#define	PIPE 5
#define ERROR_REDIRECTION_INPUT 6
#define ERROR_REDIRECTION_OUTPUT 7


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
	if (*temp == '>')
	{
		while (*temp != '\0')
		{
			if (*temp != '>')
				break ;
			count++;
			temp++;
		}
	}
	else if (*temp == '<')
	{
		while (*temp != '\0')
		{
			if (*temp != '<')
				break ;
			count++;
			temp++;
		}
	}
	if (count > 2)
	{
		if (*cmd == '>')
			return (ERROR_REDIRECTION_INPUT);
		else if (*cmd == '<')
			return (ERROR_REDIRECTION_OUTPUT);
	}
	if (strncmp(cmd, ">", ft_strlen(str)) == 0)
		return (REDIRECTION_INPUT);
	else if (strncmp(cmd, ">>", ft_strlen(str)) == 0)
		return (DOUBLE_REDIRECTION_INPUT);
	else if (strncmp(cmd, "<", ft_strlen(str)) == 0)
		return (REDIRECTION_OUTPUT);
	else if (strncmp(cmd, "<<", ft_strlen(str)) == 0)
		return (DOUBLE_REDIRECTION_OUTPUT);
	else if (strncmp(cmd, "|", ft_strlen(str)) == 0)
		return (PIPE);
	return (0);
}

void	print_error_token(int check)
{
	if (check == PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (check == ERROR_REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (check == ERROR_REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (check == REDIRECTION_INPUT || check == DOUBLE_REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (check == REDIRECTION_OUTPUT || check == DOUBLE_REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `newline'\n");
}

int	get_flag_exec(char *str)
{
	int check;
	int flag = 0;

	flag = 0;
	check = check_syntax(str);
	if (check == PIPE || check == ERROR_REDIRECTION_INPUT || check == ERROR_REDIRECTION_OUTPUT)
	{
		flag = 1;
		print_error_token(check);
	}
	else if ((check == REDIRECTION_INPUT || check == REDIRECTION_OUTPUT) && ft_strlen(str) == 1)
	{
		flag = 1;
		print_error_token(check);
	}
	else if ((check == DOUBLE_REDIRECTION_INPUT || check == DOUBLE_REDIRECTION_OUTPUT) && ft_strlen(str) == 2)
	{
		flag = 1;
		print_error_token(check);
	}
	return (flag)
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data	data;
	int		exitcode;
	int		check;
	int		flag;

	initialize_env(argv, argc, &data, envp);
	signal(SIGINT, sighandler);
	while (1)
	{
		flag = 0;
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		add_history(line);
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
