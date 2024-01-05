#include <stdlib.h>
#include "minishell.h"

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	len_src = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len_src);
}

int	ft_count_chacters_before_c(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

void	ft_free_array(char **array, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(array[i++]);
	free(array);
}

int	ft_count_words(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	while (*str != '\0')
	{
		if (*str != c)
		{
			i = ft_count_chacters_before_c(str, c);
			str += i;
			count++;
		}
		else
			str++;
	}
	return (count);
}

int	ft_add_words_to_array(char **array, char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			i = ft_count_chacters_before_c(s, c);
			array[j] = (char *)malloc(sizeof(char) * (i + 1));
			if (array[j] == NULL)
			{
				ft_free_array(array, j);
				return (0);
			}
			ft_strlcpy(array[j], s, i + 1);
			s += i;
			j++;
		}
		else
			s++;
	}
	array[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count;

	count = ft_count_words(s, c);
	array = (char **)malloc(sizeof(*array) * (count + 1));
	if (array == NULL)
		return (NULL);
	if (ft_add_words_to_array(array, s, c))
		return (array);
	else
		return (NULL);
}