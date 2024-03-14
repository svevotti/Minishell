/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:16:39 by joschka           #+#    #+#             */
/*   Updated: 2024/03/08 12:01:32 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
