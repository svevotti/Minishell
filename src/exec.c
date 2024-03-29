/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:40:05 by joschka           #+#    #+#             */
/*   Updated: 2024/03/15 16:29:21 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_path(char **paths, char *cmd)
{
	char	*cmdpath;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmdpath, X_OK) == 0)
			return (cmdpath);
		free(cmdpath);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*cmdpath;

	if (ft_strlen(cmd) == 0 || !var_exists("PATH", env))
		return (NULL);
	while (ft_strncmp(env->str, "PATH=", 5) != 0)
		env = env->next;
	paths = ft_split(env->str + 5, ':');
	cmdpath = check_path(paths, cmd);
	free_array(paths);
	return (cmdpath);
}

char	**env_to_array(t_env *env)
{
	char	**envarray;
	int		len;
	int		i;

	i = 0;
	len = env_listsize(env);
	envarray = malloc((len + 1) * sizeof(char *));
	while (env)
	{
		envarray[i] = strdup(env->str);
		i++;
		env = env->next;
	}
	envarray[i] = NULL;
	return (envarray);
}

void	exec_linux(t_data *data, t_proc *proc, t_env *env)
{
	char	**envarray;
	int		ret;

	if (proc->no_exec)
	{
		ret = proc->no_exec;
		free_data(data);
		exit(ret);
	}
	if (!proc->cmd || !proc->cmd[0])
	{
		free_data(data);
		exit(0);
	}
	precheck_path(data, proc);
	envarray = env_to_array(env);
	execve(proc->path, proc->cmd, envarray);
	free_array(envarray);
	free_data(data);
	exit(1);
}

int	exec_cmd(t_data *data, t_proc *proc, t_env *env)
{
	pid_t	pid;
	int		wstatus;
	int		statuscode;

	statuscode = -1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (statuscode);
	}
	if (pid == 0)
	{
		if (is_builtin(proc))
		{
			statuscode = exec_builtin(proc, data);
			free_data(data);
			exit(statuscode);
		}
		exec_linux(data, proc, env);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		statuscode = WEXITSTATUS(wstatus);
	return (statuscode);
}
