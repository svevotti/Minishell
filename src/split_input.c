/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:23 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:35:24 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_str_count_token(char *str, int *count)
{
	if (*str == '>')
	{
		while (*str == '>')
		{
			*count = *count + 1;
			str++;
		}
	}
	else if (*str == '<')
	{
		while (*str == '<')
		{
			*count = *count + 1;
			str++;
		}
	}
	return (str);
}

int	count_len_word(char *str)
{
	int	count;
	int	single_quote;
	int	double_quotes;

	count = 0;
	single_quote = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if (is_white_space(str) == 1 && single_quote == 0 && double_quotes == 0)
			break ;
		else if (*str == 39)
		{
			if (double_quotes == 0)
			{
				if (single_quote == 0)
					single_quote = get_quote_flag(single_quote);
				else
					single_quote = 0;
			}
		}
		else if (*str == 34)
		{
			if (single_quote == 0)
			{
				if (double_quotes == 0)
					double_quotes = get_quote_flag(double_quotes);
				else
					double_quotes = 0;
			}
		}
		count++;
		str++;
	}
	return (count);
}

int	find_len_token(char *str)
{
	int	count;

	count = 0;
	if (is_token(str) == 1)
		str = get_str_count_token(str, &count);
	else
		count = count_len_word(str);
	return (count);
}

char	*get_single_str(char *str)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;

	size_string = find_len_token(str);
	// printf("size strong %d\n", size_string);
	if (size_string == -1)
		return (NULL);
	if (size_string == -1)
		return (NULL);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
			*temp++ = *str++;
			count++;
	}
	*temp = '\0';
	return (single_str);
}

char	**split_tokens(char *str, t_data *data)
{
	char	**string_split;
	int		commands_nbr;
	int		i;
	char	*single_str;

	data->flag_quotes = 0;
	commands_nbr = count_commands(str);
	string_split = (char **)malloc(sizeof(char *) * (commands_nbr + 1));
	if (string_split == NULL)
		return (NULL);
	i = 0;
	while (i < commands_nbr)
	{
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		single_str = get_single_str(str);
		if (single_str == NULL)
			return (NULL);
		str += ft_strlen(single_str);
		string_split[i] = single_str;
		i++;
	}
	string_split[i] = NULL;
	return (string_split);
}

int	get_array_pipes(char **process, t_data *data)
{
	int		size_array_tokens;
	int		i;
	t_list	*wrapped_proc;
	t_proc	*proc;

	size_array_tokens = find_size_input_array(process);
	i = 0;
	data->procs = NULL;
	while (i < size_array_tokens)
	{
		proc = init_cmd(i);
		wrapped_proc = ft_lstnew(proc);
		proc->cmd = split_tokens(process[i], data);
		if (proc->cmd == NULL)
			return (-1);
		ft_lstadd_back(&data->procs, wrapped_proc);
		//free_array(proc->cmd);
		i++;
	}
	if (check_redirection(data) == -1)
	{
		data->exitcode = 2;
		return (ERROR);
	}
	clean_up(data->procs);
	return (0);
}
