/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/02 23:06:19 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(t_cmd *command, char *path)
{
	char	*old_path;

	(void)command;
	old_path = getcwd(0, _PC_PATH_MAX);
	if (chdir(path) == 0)
	{
		set_new_env("OLDPWD=", old_path);
		g_state.exit_status = 0;
	}
	else
	{
		printf("soobash: cd: %s: No such file or directory\n", path);
		g_state.exit_status = 1;
	}
	free(old_path);
	old_path = NULL;
	return ;
}

void	ft_cd(t_cmd *command)
{
	print_test(&command);
	if (command->argc == 1)
		change_directory(command, "HOME");
	else
		change_directory(command, command->argv[1]);
	return ;
}
