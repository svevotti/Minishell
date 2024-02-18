# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

struct s_env;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;


typedef struct s_data
{
	t_env	*env;
	char	**cmd;
}t_data;

//handle env var
int		find_size(char *str);
char	*find_name_var(char *str);
char    *print_var(char *str, int str_size, t_data *data);

//trans_env
void	trans_env(t_data *data, char **envp);
void	free_env(t_env *head);
void	exec_cmd(t_data *data);

#endif


