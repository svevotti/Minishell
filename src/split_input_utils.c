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
	return (0);
}
