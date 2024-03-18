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
	int	type;

	type = *str;
	if (*str == '>')
	{
		while (*str == '>')
		{
			*count = *count + 1;
			str++;
		}
		if (*count > 2)
		{
			if (*count == 3 && type == '>')
				print_error_token(ERROR_3REDIRECTION_INPUT);
			else if (*count > 3)
				print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
			return (NULL);
		}
	}
	else if (*str == '<')
	{
		while (*str == '<')
		{
			*count = *count + 1;
			str++;
		}
		if (*count > 2)
		{
			if (*count == 3 && type == '<')
				print_error_token(ERROR_3REDIRECTION_INPUT);
			else if (*count > 3)
				print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
			return (NULL);
		}
	}
	return (str);
}

int	count_len_word(char *str, t_data *data)
{
	int	count;
	int	single_quote;
	int	double_quotes;
	int	count_redirection;

	count = 0;
	count_redirection = 0;
	single_quote = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if (is_white_space(str) == 1 && single_quote == 0 && double_quotes == 0)
			break ;
		// if (*str == 39)
		// {
		// 	if (double_quotes == 0)
		// 	{
		// 		if (single_quote == 0)
		// 			single_quote = get_quote_flag(single_quote);
		// 		else
		// 			single_quote = 0;
		// 	}
		// 	count++;
		// 	// if (single_quote == 0 && double_quotes == 1)
		// 	// 	count++;
		// }
		// else if (*str == 34)
		// {
		// 	if (single_quote == 0)
		// 	{
		// 		if (double_quotes == 0)
		// 			double_quotes = get_quote_flag(double_quotes);
		// 		else
		// 			single_quote = 0;
		// 	}
		// 	count++;
		// 	// if (double_quotes == 0 && single_quote == 1)
		// 	// 	count++;
		// }
		// else if ((*str == '>' || *str == '<') && single_quote == 0 && double_quotes == 0)
		// {
		// 	count_redirection = check_syntax_redirection(str, data, 1);
		// 	if (count == -1)
		// 		return (ERROR);
		// 	count += count_redirection;
		// 	str += count_redirection;
		// }
		count++;
		str++;
	}
	return (count);
}

int	find_len_token(char *str, t_data *data)
{
	int	count;

	count = 0;
	if (is_token(str) == 1)
	{
		str = get_str_count_token(str, &count);
		if (str == NULL)
		{
			data->exitcode = 2;
			return (ERROR);
		}
	}
	else
		count = count_len_word(str, data);
	return (count);
}

char	*get_single_str(char *str, t_data *data)
{
	int		size_string;
	int		count;
	char	*single_str;
	char	*temp;
	int	single_quote;
	int	double_quotes;

	single_quote = 0;
	double_quotes = 0;
	size_string = find_len_token(str, data);
	if (size_string == -1)
		return (NULL);
	printf("size each command %d - cmd %s\n", size_string, str);
	if (size_string == -1)
		return (NULL);
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		// if (*str == 39)
		// {
		// 	if (double_quotes == 0)
		// 	{
		// 		if (single_quote == 0)
		// 			single_quote = 1;
		// 		str++;
		// 	}
		// 	else
		// 	{
		// 		*temp++ = *str++;
		// 		count++;
		// 	}
		// }
		// else if (*str == 34)
		// {
		// 	if (single_quote == 0)
		// 	{
		// 		if (double_quotes == 0)
		// 			double_quotes = 1;
		// 		str++;
		// 	}
		// 	else
		// 	{
		// 		*temp++ = *str++;
		// 		count++;
		// 	}
		// }
		// else
		// {
			*temp++ = *str++;
			count++;
		// }
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
	printf("command nbr %d\n", commands_nbr);
	string_split = (char **)malloc(sizeof(char *) * (commands_nbr + 1));
	if (string_split == NULL)
		return (NULL);
	i = 0;
	while (i < commands_nbr)
	{
		while (*str == ' ' || *str == '\n' || *str == '\t')
			str++;
		single_str = get_single_str(str, data);
		if (single_str == NULL)
			return (NULL);
		// if (*str == 34 || *str == 39)
		// 	str += 2;
		str += ft_strlen(single_str);
		string_split[i] = single_str;
		i++;
	}
	string_split[i] = NULL;
	return (string_split);
}

void	print_proc_items(t_list *head)
{
	t_proc	*proc;

	proc = head->content;
	printf("--- LIST ITEM PROC ---\n");
	while (head != NULL)
	{
		printf("id --> %d\n", proc->id);
		printf("path --> %s\n", proc->path);
		// printf("cmdlist --  ");
		printf("commands --  ");
		print_array(proc->cmd);
		printf("pipe in --> %d\n", proc->pipe_in);
		printf("pipe out --> %d\n", proc->pipe_out);
		printf("infile --> %s\n", proc->infile);
		printf("outfile --> %s\n", proc->outfile);
		printf("no exec --> %d\n", proc->no_exec);
		head = head -> next;
	}
	printf("--- END ---\n");
}

void	get_array_pipes(char **process, t_data *data)
{
	int		size_array_tokens;
	int		i;
	t_list	*wrapped_proc;
	t_proc	*proc;

	size_array_tokens = find_size_input_array(process);
	i = 0;
	while (i < size_array_tokens)
	{
		proc = init_cmd(i);
		wrapped_proc = ft_lstnew(proc);
		proc->cmd = split_tokens(process[i], data);
		ft_lstadd_back(&data->procs, wrapped_proc);
		i++;
	}
	print_proc_items(wrapped_proc);
}
		