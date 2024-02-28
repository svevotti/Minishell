# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

struct s_env;

typedef struct s_env
{
	char			*str;
	char			*key;
	char			*value;
	struct s_env	*next;
	int				exit_status;
}t_env;


typedef struct s_data
{
	t_env	*env;
	char	**input;
}t_data;

//handle env var
int		find_size(char *str);
char	*find_name_var(char *str);
char	*expand_input(char *str, t_data *data);
char	*get_env_value(t_env *head, char *key);

//trans_env
void	trans_env(t_data *data, char **envp);
void	free_env(t_env *head);

//split_input
char	**split_function(char *str);

#endif


