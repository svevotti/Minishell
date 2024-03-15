/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:16 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:35:18 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_token(char *str)
{
	if (*str == '|')
		return (1);
	if (*str == '>')
		return (1);
	if (*str == '<')
		return (1);
	return (0);
}

int	is_white_space(char *str)
{
	if (*str == ' ')
		return (1);
	if (*str == '\n')
		return (1);
	if (*str == '\t')
		return (1);
	if (*str == '\0')
		return (2);
	return (0);
}
