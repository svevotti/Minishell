/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:46:01 by joschka           #+#    #+#             */
/*   Updated: 2024/03/04 14:18:53 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_error(char *s, int fd)
{
	int	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

void	ft_error(char *arg, int flag)
{
	char	*str;

	if (flag == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(arg);
	}
	else if (flag == 1)
	{
		str = ft_strjoin(arg, ": command not found\n");
		ft_print_error(str, 2);
		free(str);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\n", 2);
	}
}
