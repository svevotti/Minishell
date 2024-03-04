/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:46:01 by joschka           #+#    #+#             */
/*   Updated: 2024/03/01 16:42:40 by joschka          ###   ########.fr       */
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

void	ft_error(int errnum, char *arg, int flag)
{
	char	*str;

	if (flag == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(arg);
	}
	else if (flag == 1)
	{
		str = strerror(errnum);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\n", 2);
	}
}
