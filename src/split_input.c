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

int	redirection(char *str, char *next_str, t_data *data)
{
	int	single_quote;
	int	double_quote;
	int	count;


	single_quote = 0;
	double_quote = 0;
	count = 0;
	while (*str != '\0')
	{
		if (*str == 34)
		{
			if (single_quote == 0)
			{
				if (double_quote == 0)
					double_quote = 1;
				else
					double_quote = 0;
			}
		}
		if (*str == 39)
		{
			if (double_quote == 0)
			{
				if (single_quote == 0)
					single_quote = 1;
				else
					single_quote = 0;
			}
		}
		else if (*str == '>')
		{
			if (single_quote == 0 && double_quote == 0)
			{
				count = ft_strlen(str);
				if (count > 2)
				{
					if (count == 3)
						print_error_token(ERROR_3REDIRECTION_INPUT);
					else if (count > 3)
						print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
					data->exitcode = 2;
					return (ERROR);
				}
				if (ft_strlen(next_str) == 0)
				{
					if (count == 1 || count == 2)
						print_error_token(ERROR_REDIRECTION_INPUT);
					else if (count == 3)
						print_error_token(ERROR_3REDIRECTION_INPUT);
					else if (count > 3)
						print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
					data->exitcode = 2;
					return (ERROR);
				}
				else
				{
					printf("P R E P A R E\n");
					break ;
				}
			}
		}
		else if (*str == '<')
		{
			if (single_quote == 0 && double_quote == 0)
			{
				count = ft_strlen(str);
				if (count > 2)
				{
					if (count == 3)
						print_error_token(ERROR_4REDIRECTION_OUTPUT);
					else if (count > 3)
						print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
					data->exitcode = 2;
					return (ERROR);
				}
				if (ft_strlen(next_str) == 0)
				{
					if (count == 1 || count == 2)
						print_error_token(ERROR_REDIRECTION_OUTPUT);
					else if (count == 3)
						print_error_token(ERROR_4REDIRECTION_OUTPUT);
					else if (count > 3)
						print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
					data->exitcode = 2;
					return (ERROR);
				}
				else
				{
					printf("P R E P A R E\n");
					break ;
				}
			}
		}
		str++;
	}
	return (0);
}

void	check_process(char **str, t_data *data)
{
	int i;
	int	size;

	i = 0;
	//print_array(str);
	size = find_size_input_array(str);
	while (i < size)
	{
		redirection(str[i], str[i + 1], data);
		i++;
	}
}
int check_redirection(t_data *data)
{
	t_proc *proc;
	t_list	*list_cmd;
	char	**cmd;
	int		i;

	list_cmd = data->procs;
	i = 0;
	proc = list_cmd->content;
	while (list_cmd != NULL)
	{
		check_process(proc->cmd, data);
		list_cmd = list_cmd->next;
	}
	return (0);
}

char	*get_str_no_quotes(char *str, t_data *data)
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
	single_str = (char *)malloc(sizeof(char) * (size_string + 1));
	if (single_str == NULL)
		return (NULL);
	count = 0;
	temp = single_str;
	while (count < size_string)
	{
		if (*str == 39)
		{
			if (double_quotes == 0)
			{
				if (single_quote == 0)
					single_quote = 1;
				str++;
			}
			else
			{
				*temp++ = *str++;
				count++;
			}
		}
		else if (*str == 34)
		{
			if (single_quote == 0)
			{
				if (double_quotes == 0)
					double_quotes = 1;
				str++;
			}
			else
			{
				*temp++ = *str++;
				count++;
			}
		}
		else
		{
			*temp++ = *str++;
			count++;
		}
	}
	*temp = '\0';
	return (single_str);
}

int	find_len_str(char *str)
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
		if (*str == 39)
		{
			if (double_quotes == 0)
			{
				if (single_quote == 0)
					single_quote = get_quote_flag(single_quote);
				else
					single_quote = 0;
			}
			//count++;
			if (single_quote == 0 && double_quotes == 1)
				count++;
		}
		else if (*str == 34)
		{
			if (single_quote == 0)
			{
				if (double_quotes == 0)
					double_quotes = get_quote_flag(double_quotes);
				else
					single_quote = 0;
			}
			//count++;
			if (double_quotes == 0 && single_quote == 1)
				count++;
		}
		// else if ((*str == '>' || *str == '<') && single_quote == 0 && double_quotes == 0)
		// {
		// 	count_redirection = check_syntax_redirection(str, data, 1);
		// 	if (count == -1)
		// 		return (ERROR);
		// 	count += count_redirection;
		// 	str += count_redirection;
		// }
		else
			count++;
		str++;
	}
	return (count);
}

char	*remove_quotes(char *str)
{
	int		size;
	char	*new_str;
	char	*temp;
	int		count;
	int		double_quotes;
	int		single_quotes;
	 
	
	single_quotes = 0;
	double_quotes = 0;
	size = find_len_str(str);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (new_str == NULL)
		return (NULL);
	count = 0;
	temp = new_str;
	while (count < size)
	{
		if (*str == 39)
		{
			if (double_quotes == 0)
			{
				if (single_quotes == 0)
					single_quotes = 1;
				str++;
			}
			else
			{
				*temp++ = *str++;
				count++;
			}
		}
		else if (*str == 34)
		{
			if (single_quotes == 0)
			{
				if (double_quotes == 0)
					double_quotes = 1;
				str++;
			}
			else
			{
				*temp++ = *str++;
				count++;
			}
		}
		else
		{
			*temp++ = *str++;
			count++;
		}
	}
	*temp = '\0';
	return (new_str);
}

void	check_for_quotes(char **str)
{
	int i;
	int	size;

	i = 0;
	size = find_size_input_array(str);
	while (i < size)
	{
		str[i] = remove_quotes(str[i]);
		i++;
	}
}
void	clean_up(t_list *list_proc)
{
	int		size_array_tokens;
	int		i;
	t_proc *proc;

	proc = list_proc->content;
	//size_array_tokens = find_size_input_array(process);
	i = 0;
	while (list_proc != NULL)
	{
		check_for_quotes(proc->cmd);
		list_proc = list_proc->next;
	}
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
	printf("before removing quotes\n");
	print_proc_items(wrapped_proc);
	check_redirection(data);
	clean_up(wrapped_proc);
	printf("after removing quotes\n");
	print_proc_items(wrapped_proc);
}
