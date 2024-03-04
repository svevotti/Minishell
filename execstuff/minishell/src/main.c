/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:39:46 by joschka           #+#    #+#             */
/*   Updated: 2024/03/04 14:35:47 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// to do : increment SHLVL, 
// builtins, export exitcode

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		exitcode;

	if (argc > 1)
		data.input = ft_split(argv[1], ' ');
	trans_env(&data, envp);
	exitcode = minishell(&data);
	printf("exitcode main: %d\n", exitcode);
	free_data(&data); 
	//in true minishell only free procs and input not env 
	// !!hint what about fd's ??
	return (0);
}
