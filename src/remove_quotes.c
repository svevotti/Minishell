/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:47:06 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 15:51:51 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_str_without_quotes(char *new, char *str)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*str != '\0')
	{
		if (*str == 39 && double_quotes == 0)
		{
			if (single_quotes == 0)
				single_quotes = 1;
			str++;
		}
		else if (*str == 34 && single_quotes == 0)
		{
			if (double_quotes == 0)
				double_quotes = 1;
			str++;
		}
		else
			*new++ = *str++;
	}
	*new = '\0';
}

char	*remove_quotes(char *str)
{
	int		size;
	char	*new_str;

	size = find_len_str(str);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (new_str == NULL)
		return (NULL);
	copy_str_without_quotes(new_str, str);
	return (new_str);
}

//remove quotes and redirections
t_list	*get_clean_command_list(char **tokens)
{
	int		i;
	int		size;
	char	*token;
	t_list	*wrapped_token;
	t_list	*wrapped_token_head;

	wrapped_token_head = NULL;
	i = 0;
	size = find_size_input_array(tokens);
	while (i < size)
	{
		if (is_redirection(tokens[i]))
			i++;
		else
		{
			token = remove_quotes(tokens[i]);
			wrapped_token = ft_lstnew(token);
			ft_lstadd_back(&wrapped_token_head, wrapped_token);
		}
		i++;
	}
	return (wrapped_token_head);
}

void	clean_up(t_list *list_proc)
{
	t_proc	*proc;

	while (list_proc != NULL)
	{
		proc = list_proc->content;
		proc->cmdlist = get_clean_command_list(proc->cmd);
		free_array(proc->cmd);
		list_to_array(proc);
		list_proc = list_proc->next;
	}
}
