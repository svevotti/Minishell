/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:29 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/20 11:34:27 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initialize(char **argv, char argc, t_data *data, char **envp)
{
	(void)argc;
	(void)argv;
	trans_env(data, envp);
	data->procs = NULL;
	data->exit = 0;
	data->exitcode = 0;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
}
