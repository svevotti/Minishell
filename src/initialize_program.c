/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:29 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/21 10:58:20 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	increment_shlvl(t_env *env, t_data *data)
{
	char	*value;
	int		nbr;
	t_env	*lvl;
	char	**cmd;

	nbr = 0;
	lvl = var_exists("SHLVL", env);
	if (lvl)
		nbr = ft_atoi(lvl->value);
	nbr++;
	value = ft_itoa(nbr);
	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = "export";
	cmd[1] = ft_strjoin("SHLVL=", value);
	cmd[2] = NULL;
	ft_export(cmd, data);
	free(value);
	free(cmd[1]);
	free(cmd);
}

void	initialize(char **argv, char argc, t_data *data, char **envp)
{
	(void)argc;
	(void)argv;
	trans_env(data, envp);
	increment_shlvl(data->env, data);
	data->procs = NULL;
	data->exit = 0;
	data->exitcode = 0;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
}
