/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:09 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:35:11 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_quote_flag(int flag)
{
	if (flag == 0)
		return (1);
	return (0);
}

int	is_slash(char *str)
{
	str++;
	if (*str == 92 || *str == 47)
		return (1);
	return (0);
}

int	check_name(char c)
{
	if (ft_isalpha(c) == 1)
		return (1);
	if (ft_isdigit(c) == 1)
		return (1);
	if (strncmp(&c, "_", 1) == 0)
		return (1);
	if (c == '?')
		return (1);
	return (0);
}

int	ft_strlen1(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

char	*find_name_var(char *str)
{
	char	*name_var;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen1(str);
	name_var = (char *)malloc(sizeof(char) * (len + 1));
	if (name_var == NULL)
		return (NULL);
	while (i < len)
	{
		name_var[i] = str[i];
		i++;
	}
	name_var[i] = '\0';
	return (name_var);
}
