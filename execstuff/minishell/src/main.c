/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:39:46 by joschka           #+#    #+#             */
/*   Updated: 2024/03/02 13:49:45 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// to do : handle some (pipe and fork everywhere?)errors (cmd not found error),
// builtins, ?indirect paths?

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		exitcode;

	if (argc)
		data.input = ft_split(argv[1], ' ');
	trans_env(&data, envp);
	exitcode = minishell(&data);
	printf("exitcode main: %d\n", exitcode);
	free_data(&data); 
	//in true minishell only free procs and input not env 
	// !!hint what about fd's ??
	return (0);
}
