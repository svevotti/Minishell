#include "../include/minishell.h"
#include <dirent.h>

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
	return ("does not exitst");
}

int main(int argc, char **argv, char **envp)
{
	char static *line;
	int			size_input_string;
	char		*expanded_input;
	t_data		data;
  	char     **split_input;
	char	*path_execve;
	char 	*path;
	(void)argc;
	(void)argv;
	trans_env(&data, envp);
	path = get_env_value(data.env, "PATH");
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
		print_array(split_input);
		path_execve = get_path_exec(line, path);
		printf("%s\n", path_execve);
		free(line);
	}
	return (0);
}