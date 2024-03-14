/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:38:03 by joschka           #+#    #+#             */
/*   Updated: 2024/03/11 10:37:22 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_builtin(t_proc *proc, t_data *data)
{
	int	exitstatus;

	if (proc->no_exec)
		return (proc->no_exec);
	exitstatus = 0;
	if (is_builtin(proc) == ECHO)
		exitstatus = ft_echo(proc->cmd);
	else if (is_builtin(proc) == ENV)
		ft_env(data->env);
	else if (is_builtin(proc) == EXPORT)
		exitstatus = ft_export(proc->cmd, data);
	else if (is_builtin(proc) == PWD)
		exitstatus = ft_pwd();
	else if (is_builtin(proc) == UNSET)
		ft_unset(proc->cmd, data);
	else if (is_builtin(proc) == CD)
		exitstatus = ft_cd(proc->cmd, data);
	else if (is_builtin(proc) == EXIT)
		exitstatus = ft_exit(proc->cmd, data);
	return (exitstatus);
}
