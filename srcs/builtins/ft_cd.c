/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/03 01:21:15 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(char *path)
{
	char	*old_path;
	char	*value;
	char	*pwd;

	old_path = getcwd(0, _PC_PATH_MAX);
	if (chdir(path) == 0)
	{
		pwd = getcwd(0, _PC_PATH_MAX);
		value = get_env("OLDPWD");
		if (ft_strlen(value) > 0)
			update_env("OLDPWD", old_path);
		else
			set_new_env("OLDPWD", old_path);
		update_env("PWD", pwd);
		free(value);
		free(pwd);
		g_state.exit_status = 0;
	}
	else
	{
		printf("soobash: cd: %s: No such file or directory\n", path);
		g_state.exit_status = 1;
	}
	free(old_path);
	old_path = NULL;
}

void	ft_cd(t_cmd *command)
{
	char	*home;

	home = get_env("HOME");
	if (command->argc == 1)
		change_directory(home);
	else
		change_directory(command->argv[1]);
	free(home);
	return ;
}
