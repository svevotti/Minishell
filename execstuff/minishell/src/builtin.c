/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:38:03 by joschka           #+#    #+#             */
/*   Updated: 2024/03/01 16:42:33 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char **cmd)
{
	int	i;
	int	flag;
	int	size;

	i = 1;
	flag = 0;
	size = get_arr_size(cmd);
	if (size > 1)
	{
		while (ft_strcmp(cmd[i], "-n") == 0 && cmd[i])
		{
			i++;
			flag = 1;
		}
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] && cmd[i][0])
				write(1, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}

int	exec_builtin(t_proc *proc) // + t_data *data for env and stuff
{
	int	exitstatus;

	exitstatus = 0;
	if (is_builtin(proc) == ECHO)
		exitstatus = ft_echo(proc->cmd);
	return (exitstatus);
}
