#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

# define ECHO 1
# define ENV 2

# define TRUNC_OUTFILE 1
# define APPEND_OUTFILE 2
# define INFILE 3
# define HEREDOC 4

# define ERROR -1
# define ERROR_1PIPE -1
# define ERROR_2PLUSPIPE -2
# define ERROR_REDIRECTION_INPUT -3
# define ERROR_3REDIRECTION_INPUT -4
# define ERROR_4PLUSREDIRECTION_INPUT -5
# define ERROR_REDIRECTION_OUTPUT -6
# define ERROR_4REDIRECTION_OUTPUT -7
# define ERROR_5PLUSREDIRECTION_OUTPUT -8
# define PIPE 1
# define RED_INPUT 2
# define RED_OUTPUT 3

struct	s_env;

typedef struct s_env
{
	char			*str;
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_proc
{
	int		id;
	char	*path;
	t_list	*cmdlist;
	char	**cmd;
	int		fd_in;
	int		fd_out;
	int		pipe_in;
	int		pipe_out;
	char	*infile;
	char	*outfile;
	int		exec;
}t_proc;

typedef struct s_data
{
	t_env	*env;
	t_list	*procs;
	char	**input;
}t_data;

typedef struct s_heredoc
{
	char	*ret;
	char	*tmp;
	char	*check;
}t_heredoc;

//handle env var
int		find_size(char *str, t_env *env);
char	*find_name_var(char *str);
char	*expand_input(char *str, t_data *data);
char	*get_env_value(t_env *head, char *key);

//find size env var
int		find_size(char *str, t_env *env);
int		find_len(char *str);

//trans_env
void	trans_env(t_data *data, char **envp);
void	free_env(t_env *head);

//split_input
char	**split_function(char *str);

//check first argv
void	execute_cmd(char **input, t_env *env, char **envp);

//free functions
int		free_strings(char *str1, char *str2, char **str3);
void	free_input(char **input);

//utils env var
char	*find_name_var(char *str);
int		get_quote_flag(int flag);

void	print_array(char **str);

//size split input
int		find_len(char *str);
int		find_size_array(char *str);

//utils trans env
char	**get_item(char *str, char delimiter);

//crate input pipe at the end
void	update_input(char **input);
int		find_size_input_array(char **array);

//print error
int	tokens_error(char **input);

//error message tokens
void	print_error_token(int check);
int		check_red_input(char *str, char *next_str);
int		check_red_output(char *str, char *next_str);


// builtin
int		exec_builtin(t_proc *proc, t_data *data);
int		is_builtin(t_proc *proc);
int		ft_echo(char **cmd);
int		get_arr_size(char **arr);

// free
void	free_env(t_env *head);
void	free_procs(t_list *procs);
void	free_list(t_list *lst);
void	free_array(char **arr);
void	free_data(t_data *data);

// parse
int		parse_cmds(t_data *data);
int		fill_cmd_nodes(t_list *procs, t_data *data);
t_proc	*init_cmd(int id);
void	list_to_array(t_proc *proc);
void	create_cmd_list(t_data *data);

// env
void	trans_env(t_data *data, char **envp);
void	add_env_node(t_env **head, t_env *new);
t_env	*new_node(char *str);
int		env_listsize(t_env *lst);
char	**env_to_array(t_env *env);

// executor & exec cmd
int		minishell(t_data *data);
int		run_executor(t_data *data);
int		executor(t_data *data, t_list *proc);
int		parentproc(t_data *data, t_list *proc, int parent);
int		childproc(t_data *data, t_list *proc);
int		pipe_and_fork(t_proc *proc);
int		redirect_pipe(pid_t pid, t_proc *proc, int *fd);
int		exec_cmd(t_data *data, t_proc *proc, t_env *env);
void	exec_linux(t_data *data, t_proc *proc, t_env *env);
char	*get_path(char *cmd, t_env *env);

// error
void	ft_error(char *arg, int flag);
void	ft_print_error(char *s, int fd);

//redirection
int		is_redirection(char *str);
int		prepare_redirection(t_proc *proc, char **input, int i);
void	get_filename(t_proc *proc, char *file, int type);
int		open_file(t_proc *proc, int type);
int		open_outfile(t_proc *proc, int type);
void	redirect(t_proc *proc);
int		get_heredoc(t_proc *proc, char *delimiter);
char	*get_here_str(char *delimiter);
void	init_doc(t_heredoc *doc);
char	*ft_herejoin(char *str, char *join);
char	*fill_str(char *line, char *str, char *join);

#endif