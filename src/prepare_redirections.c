/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:48:11 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 14:48:12 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
