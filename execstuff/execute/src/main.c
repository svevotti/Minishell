/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:39:46 by joschka           #+#    #+#             */
/*   Updated: 2024/02/13 13:22:28 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// void	printenv(t_env *ptr)
// {
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->str);
// 		ptr = ptr->next;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	__pid_t	pid;
 
	(void)argc;
	data.cmd = argv + 1;
	trans_env(&data, envp);
	pid = fork();
	if (pid < 0)
		printf("fork error\n");
	if (pid == 0)
		exec_cmd(&data);
	else 
	{
		wait(NULL);
	}
	// printenv(data.head);
	free_env(data.env);
	return (0);
}