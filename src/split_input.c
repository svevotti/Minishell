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
	while (i < size_array_tokens)
	{
		proc = init_cmd(i);
		wrapped_proc = ft_lstnew(proc);
		proc->cmd = split_tokens(process[i], data);
		if (proc->cmd == NULL)
			return (-1);
		ft_lstadd_back(&data->procs, wrapped_proc);
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
