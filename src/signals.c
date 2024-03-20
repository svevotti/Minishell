/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:41:17 by joschka           #+#    #+#             */
/*   Updated: 2024/03/20 12:08:20 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_sig;

void	check_for_signal(t_data *data)
{
	if (g_sig == SIGINT)
	{
		data->exitcode = 130;
		g_sig = 0;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals_main(void)
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

void	child_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 2);
	exit(130);
}

void	handle_signals_child(int pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (pid == 0)
		sa.sa_handler = child_handler;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
