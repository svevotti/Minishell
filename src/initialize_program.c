/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:29 by smazzari          #+#    #+#             */
/*   Updated: 2024/03/14 13:35:30 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	initialize_signals(void)
{
	struct sigaction	action_1;
	sigset_t			action_1_mask;
	struct sigaction	action_2;
	sigset_t			action_2_mask;

	sigemptyset(&action_1_mask);
	sigaddset(&action_1_mask, SIGINT);
	action_1.sa_handler = sig_handler;
	action_1.sa_mask = action_1_mask;
	action_1.sa_flags = 0;
	sigaction(SIGINT, &action_1, NULL);
	sigemptyset(&action_2_mask);
	sigaddset(&action_2_mask, SIGQUIT);
	action_2.sa_handler = SIG_IGN;
	action_2.sa_mask = action_2_mask;
	action_2.sa_flags = 0;
	sigaction(SIGQUIT, &action_2, NULL);
}

void	initialize(char **argv, char argc, t_data *data, char **envp)
{
	(void)argc;
	(void)argv;
	trans_env(data, envp);
	data->input = NULL;
	data->exit = 0;
	data->exitcode = 0;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	initialize_signals();
}
