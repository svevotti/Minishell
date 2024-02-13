# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//handle env var
int		find_size(char *str);
char	*find_name_var(char *str);
char    *print_env_var(char *str, int str_size);





#endif


