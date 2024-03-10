#include "../include/minishell.h"
#define	PIPE_END -2

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

void *get_cmd_pipes(void)
{
	int		new_pipe;
	char	*prompt;
	// int		*size_array;
	// char	*array_pipes;

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

// void	update_input(char **input)
// {
// 	// int	size_input;
// 	// int	size_new_input;
// 	// char	**new_input;
// 	// char	*str_new_pipes;
// 	// char	*str;


// 	// size_input = find_size_input_array(input);
// 	// size_new_input = find_size_pipe_end(input[size_input - 1] + size_input);
// 	// new_input = (char **)malloc(sizeof(char *) * (size_new_input + 1));
// 	// get_cmd_pipes();
// 	//new_input[i] = NULL;

// 	// get_cmd = input[size_input - 1];
// 	// int count = 0;
// 	// while (new_pipe == 1)
// 	// {
// 	// 	new_pipe = 0;
// 	// 	count++;
// 	// 	if (strcmp(get_cmd, "|") == 0)
// 	// 	{
// 	// 		prompt = readline("~");
// 	// 		temp = prompt;
// 	// 		int	size_prompt = ft_strlen(prompt);
// 	// 		temp += size_prompt - 1;
// 	// 		while (*temp == ' ' || *temp == '\n' || *temp == '\t')
// 	// 			temp--;
// 	// 		if (*temp == '|')
// 	// 			new_pipe = 1;
// 	// 	}
// 	// }
// 	// printf("count pipes in prompt %d\n", count);
// }
