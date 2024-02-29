
#include "../include/minishell.h"
#include <dirent.h>
#include <sys/stat.h>

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