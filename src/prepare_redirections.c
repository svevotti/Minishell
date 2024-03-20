#include "../include/minishell.h"

int	check_next_str(char *str, char *next_str, int type)
{
	int	count;

	count = ft_strlen(str);
	if (next_str == NULL && type == RED_INPUT)
	{
		if (count == 1 || count == 2)
			print_error_token(ERROR_REDIRECTION_INPUT);
		else if (count == 3)
			print_error_token(ERROR_3REDIRECTION_INPUT);
		else if (count > 3)
			print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
		return (ERROR);
	}
	else if (next_str == NULL && type == RED_OUTPUT)
	{
		if (count == 1 || count == 2)
			print_error_token(ERROR_REDIRECTION_OUTPUT);
		else if (count == 3)
			print_error_token(ERROR_4REDIRECTION_OUTPUT);
		else if (count > 3)
			print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
		return (ERROR);
	}
	return (0);
}

int	check_error_redirection(char *str, int type)
{
	int	len;

	len = ft_strlen(str);
	if (len > 2)
	{
		if (type == RED_INPUT)
		{
			if (len == 3)
				print_error_token(ERROR_3REDIRECTION_INPUT);
			else if (len > 3)
				print_error_token(ERROR_4PLUSREDIRECTION_INPUT);
			return (ERROR);
		}
		else
		{
			if (len == 3)
				print_error_token(ERROR_4REDIRECTION_OUTPUT);
			else if (len > 3)
				print_error_token(ERROR_5PLUSREDIRECTION_OUTPUT);
		}
		return (ERROR);
	}
	return (0);
}

int	check_syntax_redirection(char *str, char *next_str, t_proc *proc)
{
	if (*str == '>')
	{
		if (check_error_redirection(str, RED_INPUT) == -1)
			return (ERROR);
		if (check_next_str(str, next_str, RED_INPUT) == -1)
			return (ERROR);
		else
		{
			next_str = remove_quotes(next_str);
			prepare_redirection(proc, str, next_str);
		}
	}
	else
	{
		if (check_error_redirection(str, RED_OUTPUT) == -1)
			return (ERROR);
		if (check_next_str(str, next_str, RED_OUTPUT) == -1)
			return (ERROR);
		else
		{
			next_str = remove_quotes(next_str);
			prepare_redirection(proc, str, next_str);
		}
	}
	return (0);
}

int	redirection(char *str, char *next_str, t_proc *proc)
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
			get_flag(&single_quote, &double_quote, *str);
		else if (*str == 39)
			get_flag(&single_quote, &double_quote, *str);
		else if (is_redirection(str) && single_quote == 0 && double_quote == 0)
		{
			if (check_syntax_redirection(str, next_str, proc) == -1)
				return (ERROR);
			else
				return (1);
		}
		str++;
	}
	return (0);
}

int	check_process(char **str, t_proc *proc, t_data *data)
{
	int	i;
	int	size;
	int	check;
	
	check = 0;
	i = 0;
	size = find_size_input_array(str);
	while (i < size)
	{
		check = redirection(str[i], str[i + 1], proc);
		if (check == -1)
		{
			data->exitcode = 2;
			return (ERROR);
		}
		else if (check == 1)
			i++;
		i++;
	}
	return (0);
}

int	check_redirection(t_data *data)
{
	t_proc	*proc;
	t_list	*list_cmd;

	list_cmd = data->procs;
	while (list_cmd != NULL)
	{
		proc = list_cmd->content;
		if (check_process(proc->cmd, proc, data) == -1)
			return (ERROR);
		list_cmd = list_cmd->next;
	}
	return (0);
}
