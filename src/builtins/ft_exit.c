/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:25:20 by joschka           #+#    #+#             */
/*   Updated: 2024/03/14 15:57:12 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **cmd, t_data *data)
{
	int	ret;

	ret = data->exitcode;
	if (data->exit)
		ft_putstr_fd("exit\n", 2);
	if (cmd[1])
	{
		if (!ft_isnumber(cmd[1]))
		{
			exit_error(cmd[1], 1);
			ret = 2;
		}
		else
		{
			ret = ft_atoi(cmd[1]);
			if (cmd[2])
			{
				exit_error(NULL, 0);
				return (1);
			}
		}
	}
	free_data(data);
	exit(ret);
}
