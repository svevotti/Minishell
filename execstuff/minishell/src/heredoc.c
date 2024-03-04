/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:38:36 by joschka           #+#    #+#             */
/*   Updated: 2024/03/01 16:42:57 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fill_str(char *line, char *str, char *join)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (str)
	{
		while (str[i])
		{
			line[i] = str[i];
			i++;
		}
	}
	if (join)
	{
		while (join[k])
		{
			line[i] = join[k];
			k++;
			i++;
		}
	}
	line[i] = '\0';
	return (line);
}

char	*ft_herejoin(char *str, char *join)
{
	int		len;
	char	*line;

	if (!str && !join)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(join);
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	line = fill_str(line, str, join);
	return (line);
}

void	init_doc(t_heredoc *doc)
{
	doc->check = NULL;
	doc->ret = NULL;
	doc->tmp = NULL;
}

char	*get_here_str(char *delimiter)
{
	t_heredoc	doc;

	init_doc(&doc);
	while (1)
	{
		doc.check = readline("> ");
		if (!ft_strcmp(doc.check, delimiter))
		{
			free(doc.check);
			break ;
		}
		doc.tmp = ft_herejoin(doc.check, "\n");
		free(doc.check);
		if (!doc.ret)
			doc.ret = ft_strdup(doc.tmp);
		else
		{
			doc.check = doc.ret;
			doc.ret = ft_herejoin(doc.ret, doc.tmp);
			free(doc.check);
		}
		free(doc.tmp);
	}
	return (doc.ret);
}

int	get_heredoc(t_proc *proc, char *delimiter)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	str = get_here_str(delimiter);
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	free(str);
	proc->fd_in = fd[0];
	return (0);
}
