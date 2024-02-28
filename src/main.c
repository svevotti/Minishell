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

char	*get_path_exec(char *str, char *path_value)
{
	char			**path_folders;
	DIR				*folder;
  	struct dirent	*dir;
	int				i;
	int				count;

	path_folders = ft_split(path_value, ':');
	i = 0;
	while (path_folders[i] != NULL)
		i++;
	count = i;
	i = 0;
	while (i < count)
	{
		folder = opendir(path_folders[i]);
		if (folder == NULL)
			i++;
		else
		{
			while ((dir = readdir(folder)) != NULL)
			{
				if (strncmp(str, dir->d_name, ft_strlen(dir->d_name)) == 0)
				{
					closedir(folder);
					return (path_folders[i]);
				}
			}
			closedir(folder);
			i++;
		}
	}
	return (NULL);
}

char	*create_path_info(char *path, char *cmd)
{
	char *full_path;
	int size;
	
	size = ft_strlen(path) + ft_strlen(cmd) + 1;
	full_path = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(full_path, path, ft_strlen(path) + 1);
	ft_strlcat(full_path, "/", ft_strlen(path) + 1 + 2);
	ft_strlcat(full_path, cmd, size + 1);
	return (full_path);
}

char *get_cmd(char *str)
{
	int	i;
	int	size;
	char	*cmd;

	i = ft_strlen(str);
	size = 0;
	while (i > 0)
	{
		if (str[i] == '/')
			break ;
		size++;
		i--;
	}
	cmd = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(cmd, str + i + 1, size + 1);
	return (cmd);
}

void execute_cmd(char **input, t_env *env, char **envp)
{
	char *cmd_path;
	char *env_var_value;
	struct stat stats;
	char	*cat_path;
	char	**argvs;
	char	*str;
	char	*cmd;
	int		flag;

	flag = 0;
	env_var_value = get_env_value(env, "PATH");
	str = input[0];
	if (*str == '/' || *str == '.')
	{
		cmd_path = input[0];
		cmd = get_cmd(cmd_path);
		input[0] = cmd;
		argvs = input;
		flag = 1;
	}
	else
	{
		cmd_path = get_path_exec(input[0], env_var_value);
		cmd = input[0];
		argvs = input;
	}
	if (cmd_path != NULL)
	{
		if (flag == 0)
			cat_path = create_path_info(cmd_path, cmd);
		else
			cat_path = str;
		if (stat(cat_path, &stats) == 0)
		{
			if (stats.st_mode & X_OK)
				execve(cat_path, argvs, envp);
			else
				printf("error\n");
		}
	}
	else
	{
		env->exit_status = 127;	
		printf("error, not a command\n");
	}
}

// void	read_path(char **input, char **envp)
// {
// 	char *path;

// 	if (input[0] == NULL)
// 	{
// 		printf("error\n");
// 		return;
// 	}
// 	path = ft_strdup(input[0]);
// 	char *temp;
// 	temp = path;
// 	while(*temp != '\0')
// 	{
// 		if (*temp == '/')
// 		{
// 			printf("absolute path\n");
// 			return;
// 		}
// 		else if (*temp == '.')
// 		{
// 			printf("relative path\n");
// 			return;

// 		}
// 		temp++;
// 	}
// 	//make it work with execve
// 	printf("not a folder\n");
// }

int main(int argc, char **argv, char **envp)
{
	char static *line;
	int			size_input_string;
	char		*expanded_input;
	t_data		data;
  	char     **split_input;
	pid_t	id;
	int		status;
	int		exit_s;

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
		print_array(split_input);
		exit(1);
		id = fork();
		if (id == 0)
			execute_cmd(split_input, data.env, envp);
		else if (id < 0)
			printf("error id\n");
		else
		{
			wait(&status);
			int status_code = WEXITSTATUS(status);
			data.env->exit_status = status_code;
		}
		printf("exit status was %d\n", data.env->exit_status);
		// read_path(split_input, data.env);
		// print_array(split_input);
		//printf("%s\n", path_execve);
		free(line);
	}
	return (0);
}

// pid_t parent = getpid();
// pid_t pid = fork();

// if (pid == -1)
// {
//     // error, failed to fork()
// } 
// else if (pid > 0)
// {
//     int status;
//     waitpid(pid, &status, 0);
// }
// else 
// {
//     // we are the child
//     execve(...);
//     _exit(EXIT_FAILURE);   // exec never returns
// }