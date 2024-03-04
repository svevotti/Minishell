/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:52:26 by joschka           #+#    #+#             */
/*   Updated: 2024/03/04 14:19:53 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (TRUNC_OUTFILE);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND_OUTFILE);
	else if (!ft_strcmp(str, "<"))
		return (INFILE);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else
		return (0);
}

int	is_builtin(t_proc *proc)
{
	if (!ft_strcmp(proc->cmd[0], "echo"))
		return (ECHO);
	else
		return (0);
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	env_listsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
