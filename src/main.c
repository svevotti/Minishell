#include "../include/minishell.h"

void print_array(char **str)
{
	int i = 0;
	
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char *get_output(char *str, int str_size)
{
	char *new_string;
	int	i;
	int	j;
	int	flag_single_quote;
	char	*name_var;
	char	*value_var;
	int		len_var;
	int		tot_size;

	new_string = (char *)malloc(sizeof(char) * (str_size + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	j = 0;
	flag_single_quote = 0;
	len_var = 0;
	tot_size = 0;
	int k;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
		{
			if (flag_single_quote == 0)
				flag_single_quote = 1;
			else
				flag_single_quote = 0;
			new_string[j] = str[i];
			j++;
			i++;
		}
		else if (str[i] == '$' && flag_single_quote == 0)
		{
			k = 0;
			i++;
			name_var = find_name_var(str + i);
			//printf("name var %s\n", name_var);
			value_var = getenv(name_var);
			//printf("value var %s\n", value_var);
			len_var = ft_strlen(value_var);
			//printf("value var size %d\n", len_var);
			while (k < len_var)
			{
				new_string[j] = value_var[k];
				j++;
				k++;	
			}
			i += ft_strlen(name_var);
			// printf("new string %s\n", new_string);
		}
		else
		{
			new_string[j] = str[i];
			j++;
			i++;
		}
	}
	return (new_string);
}
int main(void)
{
	char static *line;
	char		*input_string;
	char		**array_commands;
	int			size_input_string;
	char		*string_to_print;

	while (1)
	{
		line = readline("Minishell >> ");
		if (line == NULL)
			return (1);
		add_history(line);
		input_string = line;
		size_input_string = find_size(input_string);
		//printf("find input size %d\n", size_input_string);
		// string_to_print = (char *)malloc(sizeof(char) * (size_input_string + 1));
		// if (string_to_print == NULL)
		// 	return (1);
		string_to_print = get_output(input_string, size_input_string);
		printf("%s - %d\n", string_to_print, ft_strlen(string_to_print));
		free(line);
	}

	return (0);
}