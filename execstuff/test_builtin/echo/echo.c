/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:59:02 by jbeck             #+#    #+#             */
/*   Updated: 2024/02/06 16:02:08 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	getsize(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	flag;
	int	size;

	i = 1;
	flag = 0;
	size = getsize(cmd);
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

int	main(int argc, char **argv)
{
	(void)argc;
	ft_echo(argv + 1);
	return (0);
}