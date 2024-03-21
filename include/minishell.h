/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:32:21 by jbeck             #+#    #+#             */
/*   Updated: 2024/03/21 11:16:18 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# define SUCCESS 0
# define EMPTY 1

# define ECHO	1
# define ENV	2
# define EXPORT	3
# define PWD	4
# define UNSET	5
# define CD		6
# define EXIT	7

# define ANSI_RESET		"\x1b[0m"
# define ANSI_RED		"\x1b[31m"
# define ANSI_GREEN		"\x1b[32m"
# define ANSI_YELLOW	"\x1b[33m"
# define ANSI_BLUE		"\x1b[34m"
# define ANSI_MAGENT	"\x1b[35m"
# define ANSI_CYAN		"\x1b[36m"

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
# define RED_INPUT 1
# define RED_OUTPUT 2

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
	int		no_exec;
}t_proc;

typedef struct s_data
{
	t_env	*env;
	t_list	*procs;
	char	*line;
	int		std_in;
	int		std_out;
	int		exit;
	int		exitcode;
	int		flag_quotes;
	int		exit_fd[2];
}t_data;

typedef struct s_heredoc
{
	char	*ret;
	char	*tmp;
	char	*check;
}t_heredoc;

//initialize program.c
void	initialize(char **argv, char argc, t_data *data, char **envp);

//create env.c
void	trans_env(t_data *data, char **envp);
void	free_env(t_env *head);
//utils env var
char	*find_name_var(char *str);
int		check_name(char c);
int		get_quote_flag(int flag);
int		is_slash(char *str);
//utils trans env.c
char	**get_item(char *str, char delimiter);

//env variables
//handle_env_var.c
int		find_size(char *str, t_data *data);
char	*find_name_var(char *str);
char	*expand_input(char *str, t_data *data);
char	*get_env_value(t_env *head, char *key);
//find size env var.c
int		find_len(char *str);
//utils.c
char	*get_value(char *str, t_data *data, int *len_word);

//create processes
//split processes.c
char	**split_pipes(char *str, t_data *data);
void	get_flag(int *single_quotes, int *double_quotes, char quote);
//find size.c
int		find_size_input_array(char **array);
//get size.c
int		find_len(char *str);
int		count_commands(char *str);
char	*traverse_token(char *str);

//create list procs
int		get_array_pipes(char **process, t_data *data);
char	*get_single_str(char *str);
//utils split input
int		is_white_space(char *str);
int		is_token(char *str);

//prepare redirection.c
//prepare tokens
int		check_redirection(t_data *data);
//check redirection.c
int		check_syntax_redirection(char *str, char *next_str, t_proc *proc);
//check file name.c
int		check_file_name(char *str, int size);

//clean up.c
//remove quotes
char	*remove_quotes(char *str);
void	clean_up(t_list *list_proc);
//utils.c
int		find_len_str(char *str);

//errors
void	print_error_token(int check);
int		check_syntax_pipes(char *str, t_data *data, int check);

// builtin
int		exec_builtin(t_proc *proc, t_data *data);
int		is_builtin(t_proc *proc);
int		ft_echo(char **cmd);
int		get_arr_size(char **arr);
void	ft_unset(char **cmd, t_data *data);
void	ft_env(t_env *env);
int		ft_export(char **cmd, t_data *data);
int		ft_pwd(void);
char	*get_identifier(char *arg);
t_env	*var_exists(char *str, t_env *env);
int		ft_cd(char **cmd, t_data *data);
int		ft_exit(char **cmd, t_data *data);

// free
void	free_env(t_env *head);
void	free_procs(t_list *procs);
void	free_list(t_list *lst);
void	free_array(char **arr);
void	free_data(t_data *data);

// parse
t_proc	*init_cmd(int id);
void	list_to_array(t_proc *proc);

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
void	precheck_path(t_data *data, t_proc *proc);

// error
void	ft_error(char *arg, int flag);
void	ft_print_error(char *s, int fd);
void	export_error(char *arg);
void	cd_error(char *arg, int flag);
void	exit_error(char *str, int flag);
void	ft_path_error(char *arg, int flag);

//redirection
int		is_redirection(char *str);
void	prepare_redirection(t_proc *proc, char *redirection, char *file_name);
void	get_filename(t_proc *proc, char *file, int type);
int		open_file(t_proc *proc, int type);
int		open_outfile(t_proc *proc, int type);
void	redirect(t_proc *proc);
int		get_heredoc(t_proc *proc, char *delimiter);
char	*get_here_str(char *delimiter);
void	init_doc(t_heredoc *doc);
char	*ft_herejoin(char *str, char *join);
char	*fill_str(char *line, char *str, char *join);

//signals
void	handle_signals_child(int pid);
void	handle_signals_main(void);
void	check_for_signal(t_data *data);

#endif