#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


struct s_env;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}t_env;


typedef struct s_data
{
	t_env	*env;
	char	**cmd;
}t_data;


void	trans_env(t_data *data, char **envp);
void	free_env(t_env *head);
void	exec_cmd(t_data *data);

#endif


