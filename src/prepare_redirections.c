#include "../include/minishell.h"

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
					return (ERROR);
				}
				else
				{
					t_list *list_proc;

					list_proc = data->procs;
					prepare_redirection(list_proc->content, str, next_str);
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
					t_list *list_proc;

					list_proc = data->procs;
					prepare_redirection(list_proc->content, str, next_str);
					break ;
				}
			}
		}
		str++;
	}
	return (0);
}

int	check_process(char **str, t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = find_size_input_array(str);
	while (i < size)
	{
		if (redirection(str[i], str[i + 1], data) == -1)
			return (ERROR);
		i++;
	}
	return (0);
}

int	check_redirection(t_data *data)
{
	t_proc	*proc;
	t_list	*list_cmd;

	list_cmd = data->procs;
	proc = list_cmd->content;
	while (list_cmd != NULL)
	{
		if (check_process(proc->cmd, data) == -1)
			return (ERROR);
		list_cmd = list_cmd->next;
	}
	return (0);
}
