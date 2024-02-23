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

int	find_size_array(char *str)
{
	int count;
	int	word;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	word = 1;
	while (*str != '\0')
	{
		count++;
		word = 1;
		while (word == 1)
		{
			word = 0;
			if (*str != 39 && *str != 34 && *str != ' ' && *str != '\n' && *str != '\t' && *str != '\0')
			{
				word = 1;
				while (*str != 39 && *str != 34 && *str != ' ' && *str != '\n' && *str != '\t' && *str != '\0')
					str++;
			}
			else if (*str == 39)
			{
				word = 1;
				str++;
				while (*str != 39)
					str++;
				str++;
			}
			else if (*str == 34)
			{
				word = 1;
				str++;
				while (*str != 34)
					str++;
				str++;
			}
		}
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
	}
	return (count);
}

int find_len(char *str)
{
	int count;
	int	single_quote;
	int	double_quotes;

	while (*str == ' ' || *str == '\n' || *str == '\t')
		str++;
	count = 0;
	single_quote = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if ((*str == ' ' || *str == '\n' || *str == '\t') && single_quote == 0 && double_quotes == 0)
			break ;
		if (*str == 39)
		{
			if (single_quote == 0)
				single_quote = 1;
			else
				single_quote = 0;
		}
		else if (*str == 34)
		{
			if (double_quotes == 0)
				double_quotes = 1;
			else
				double_quotes = 0;
		}
		else
			count++;
		str++;
	}
	return (count);
}

char	**split_function(char *str)
{
	char	**string_split;
	int		size_array;
	int		i;
	int		size_string;
	int		count;
	char 	*single_str;
	char	*temp;

	i = 0;
	size_string = 0;
	size_array = find_size_array(str);
	string_split = (char **)malloc(sizeof(char *) * (size_array + 1));
	while (i < size_array)
	{
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		size_string = find_len(str);
		single_str = (char *)malloc(sizeof(char) * (size_string + 1));
		count = 0;
		temp = single_str;
		while (count < size_string)
		{
			if (*str == 39 || *str == 34)
				str++;
			else 
			{
				*temp = *str;
				temp++;
				str++;
				count++;
			}
		}
		*temp = '\0';
		string_split[i] = single_str;
		str++;
		i++;
	}
	string_split[i] = NULL;
	return(string_split);
}

// void	printenv(t_env *ptr)
// {
// 	while (ptr)
// 	{
// 		printf("%s ~ %s\n", ptr->key, ptr->value);
// 		ptr = ptr->next;
// 	}
// }

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