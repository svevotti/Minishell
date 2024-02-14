/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:38:40 by jbeck             #+#    #+#             */
/*   Updated: 2024/02/08 14:13:47 by jbeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	err;
	int	fd;
	err = 0;
	if (argc > 1)
	{
		err = chdir(argv[1]);
	}
	fd = open("test.txt", O_RDONLY);
	printf("%d\n", fd);
	printf("%d\n", err);
	if (fd < 0)
		printf("could not open file");
	if (err)
		return (1);
	close(fd);
	return (0);
}