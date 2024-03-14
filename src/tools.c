/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:52:26 by joschka           #+#    #+#             */
/*   Updated: 2024/03/11 13:37:30 by joschka          ###   ########.fr       */
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
	if (!ft_strcmp(proc->cmd[0], "env"))
		return (ENV);
	if (!ft_strcmp(proc->cmd[0], "export"))
		return (EXPORT);
	if (!ft_strcmp(proc->cmd[0], "pwd"))
		return (PWD);
	if (!ft_strcmp(proc->cmd[0], "unset"))
		return (UNSET);
	if (!ft_strcmp(proc->cmd[0], "cd"))
		return (CD);
	if (!ft_strcmp(proc->cmd[0], "exit"))
		return (EXIT);
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

char	*get_identifier(char *arg)
{
	char	*str;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		str[i] = arg[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
