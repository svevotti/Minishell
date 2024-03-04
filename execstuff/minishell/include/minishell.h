/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:45:55 by joschka           #+#    #+#             */
/*   Updated: 2024/03/04 15:03:26 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define TRUNC_OUTFILE 1
# define APPEND_OUTFILE 2
# define INFILE 3
# define HEREDOC 4

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

