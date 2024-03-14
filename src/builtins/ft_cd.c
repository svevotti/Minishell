/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschka <joschka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:18:30 by joschka           #+#    #+#             */
/*   Updated: 2024/03/11 13:39:12 by joschka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_args(char **cmd)
{
	if (!cmd[1])
	{
		cd_error("no directory specified: cd [directory]", 0);
		return (1);
	}
	else if (cmd[2])
	{
		cd_error("too many arguments", 0);
		return (2);
	}
	else
		return (0);
}

void	update_var(char *str, t_data *data)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = "export";
	cmd[1] = str;
	cmd[2] = NULL;
	ft_export(cmd, data);
	free(str);
	free(cmd);
}

int	for_the_f_norm(char *path, char *to_free)
{
	if (chdir(path) == -1)
	{
		cd_error(path, 1);
		free(to_free);
		return (1);
	}
	return (0);
}

int	ft_cd(char **cmd, t_data *data)
{
	char	*oldpwd;
	t_env	*pwd;
	char	*cwd;

	if (check_args(cmd))
		return (1);
	pwd = var_exists("PWD=", data->env);
	if (!pwd)
		oldpwd = ft_strdup("PWD=");
	else
		oldpwd = ft_strjoin("OLDPWD=", pwd->value);
	if (for_the_f_norm(cmd[1], oldpwd))
		return (1);
	if (pwd)
	{
		cwd = getcwd(NULL, 0);
		update_var(ft_strjoin("PWD=", cwd), data);
		free(cwd);
	}
	if (var_exists("OLDPWD=", data->env))
		update_var(oldpwd, data);
	else
		free(oldpwd);
	return (0);
}
