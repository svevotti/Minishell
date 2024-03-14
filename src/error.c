/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:46:01 by joschka           #+#    #+#             */
/*   Updated: 2024/03/11 15:34:11 by joschka          ###   ########.fr       */
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

void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	cd_error(char *arg, int flag)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (flag == 0)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (flag == 1)
		perror(arg);
}

void	exit_error(char *str, int flag)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (flag)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
		ft_putstr_fd("too many arguments\n", 2);
}
