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


// char	*get_path_exec(char *str, char *path_value)
// {
// 	char			**path_folders;
// 	DIR				*folder;
//   	struct dirent	*dir;
// 	int				i;
// 	int				count;

// 	path_folders = ft_split(path_value, ':');
// 	i = 0;
// 	while (path_folders[i] != NULL)
// 		i++;
// 	count = i;
// 	i = 0;
// 	while (i < count)
// 	{
// 		folder = opendir(path_folders[i]);
// 		if (folder == NULL)
// 			i++;
// 		else
// 		{
// 			while ((dir = readdir(folder)) != NULL)
// 			{
// 				if (strncmp(str, dir->d_name, ft_strlen(dir->d_name)) == 0)
// 				{
// 					closedir(folder);
// 					return (path_folders[i]);
// 				}
// 			}
// 			closedir(folder);
// 			i++;
// 		}
// 	}
// 	return (NULL);
// }

// char	*create_path_info(char *path, char *cmd)
// {
// 	char *full_path;
// 	int size;
	
// 	size = ft_strlen(path) + ft_strlen(cmd) + 1;
// 	full_path = (char *)malloc(sizeof(char) * (size + 1));
// 	ft_strlcpy(full_path, path, ft_strlen(path) + 1);
// 	ft_strlcat(full_path, "/", ft_strlen(path) + 1 + 2);
// 	ft_strlcat(full_path, cmd, size + 1);
// 	return (full_path);
// }

// char *get_cmd(char *str)
// {
// 	int	i;
// 	int	size;
// 	char	*cmd;

// 	i = ft_strlen(str);
// 	size = 0;
// 	while (i > 0)
// 	{
// 		if (str[i] == '/')
// 			break ;
// 		size++;
// 		i--;
// 	}
// 	cmd = (char *)malloc(sizeof(char) * (size + 1));
// 	ft_strlcpy(cmd, str + i + 1, size + 1);
// 	return (cmd);
// }

// void execute_cmd(char **input, t_env *env, char **envp)
// {
// 	char *cmd_path;
// 	char *env_var_value;
// 	struct stat stats;
// 	char	*cat_path;
// 	char	**argvs;
// 	char	*str;
// 	char	*cmd;
// 	int		flag;

// 	flag = 0;
// 	env_var_value = get_env_value(env, "PATH");
// 	str = input[0];
// 	if (*str == '/' || *str == '.')
// 	{
// 		cmd = get_cmd(input[0]);
// 		cmd_path = get_path_exec(cmd, env_var_value);
// 		input[0] = cmd;
// 		argvs = input;
// 		flag = 1;
// 	}
// 	else
// 	{
// 		cmd_path = get_path_exec(input[0], env_var_value);
// 		cmd = input[0];
// 		argvs = input;
// 	}
// 	if (cmd_path != NULL)
// 	{
// 		if (flag == 0)
// 			cat_path = create_path_info(cmd_path, cmd);
// 		else
// 			cat_path = str;
// 		if (stat(cat_path, &stats) == 0)
// 		{
// 			if (stats.st_mode & X_OK)
// 				execve(cat_path, argvs, envp);
// 			else
// 				printf("error\n");
// 		}
// 	}
// 	else
// 	{
// 		// env->exit_status = 127;
// 		printf("error, not a command\n");
// 	}
// }

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
	else if (strncmp(cmd, ">>", ft_strlen(str)) == 0)
		return (DOUBLE_REDIRECTION_OUTPUT);
	else if (strncmp(cmd, "|", ft_strlen(str)) == 0)
		return (PIPE);
	return (0);
}

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);
}

void	print_error_token(int check)
{
	if (check == PIPE)
		printf("bash: syntax error near unexpected token `|\n");
	else if (check == ERROR_REDIRECTION_INPUT)
		printf("bash: syntax error near unexpected token `>\n");
	else if (check == ERROR_REDIRECTION_OUTPUT)
		printf("bash: syntax error near unexpected token `<\n");
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
		check = check_syntax(line);
		if (check == PIPE || check == ERROR_REDIRECTION_INPUT || check == ERROR_REDIRECTION_OUTPUT)
		{
			flag = 1;
			print_error_token(check);
		}
		if (flag == 0) {
			data.input = get_split_input(line, &data);
			// free(line);
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
