/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:32:07 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/30 21:50:11 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("pwd", cmd, 4) || \
	!ft_strncmp("export", cmd, 6) || !ft_strncmp("unset", cmd, 6) || \
	!ft_strncmp("env", cmd, 4) || !ft_strncmp("exit", cmd, 5) || !ft_strncmp("cd", cmd, 3))
		return (1);
	return (0);
}

int	exec_built_in(t_cmd *command)
{
	// 빌트인 명령 실행
	//print_test(&command);
	if (!ft_strncmp(command->cmd, "echo", ft_strlen(command->cmd) + 1))
		ft_echo(command);
	else if (!ft_strncmp(command->cmd, "cd", ft_strlen(command->cmd) + 1))
		ft_cd(command);
	else if (!ft_strncmp(command->cmd, "env", ft_strlen(command->cmd) + 1))
		ft_env(command);
	else if (!ft_strncmp(command->cmd, "pwd", ft_strlen(command->cmd) + 1))
		ft_pwd(command);
	else if (!ft_strncmp(command->cmd, "exit", ft_strlen(command->cmd) + 1))
		ft_exit(command);
	else if (!ft_strncmp(command->cmd, "unset", ft_strlen(command->cmd) + 1))
		ft_unset(command);
	else if (!ft_strncmp(command->cmd, "export", ft_strlen(command->cmd) + 1))
		ft_export(command);
	exit(1); // 무조건 있어야 함
	return (SUCCESS);
}
