#include "../include/minishell.h"
#include <signal.h>

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

void	initialize_env(char **argv, char argc, t_data *data, char **envp)
{
	(void)argc;
	(void)argv;
	trans_env(data, envp);
}