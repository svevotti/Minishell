#include "../include/minishell.h"

int	get_single_quote_flag(int flag)
{
	if (flag == 0)
		return (1);
	return (0);
}

int	ft_strlen1(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		if (ft_isalpha(*str) == 1)
			len++;
		else
			break ;
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
		if (ft_isalpha(str[i]) == 1)
			name_var[i] = str[i];
		else
			break ;
		i++;
	}
	name_var[i] = '\0';
	return (name_var);
}