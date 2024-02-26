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
				if (strncmp(str, dir->d_name, ft_strlen(str)) == 0)
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

void execute_cmd(char **input, t_env *env)
{
	char *cmd_path;
	char *env_var_value;
	struct stat stats;
	char	*cat_path;

	env_var_value = get_env_value(env, "PATH");
	cmd_path = get_path_exec(input[0], env_var_value);
	cat_path = create_path_info(cmd_path, input[0]);
	if (cmd_path != NULL)
	{
		if (stat(cmd_path, &stats) == 0)
		{
			if (stats.st_mode & X_OK)
        		printf("execute\n");
			else
				printf("not exectuable\n");
		}
	}
	else	
		printf("error\n");
}

int main(int argc, char **argv, char **envp)
{
	char static *line;
	int			size_input_string;
	char		*expanded_input;
	t_data		data;
  	char     **split_input;

	(void)argc;
	(void)argv;
	trans_env(&data, envp);
	while (1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			exit(1);
		}
		add_history(line);
		size_input_string = find_size(line);
		expanded_input = expand_input(line, size_input_string, &data);
		split_input = split_function(expanded_input);
		execute_cmd(split_input, data.env);
		// print_array(split_input);
		//printf("%s\n", path_execve);
		free(line);
	}
	return (0);
}