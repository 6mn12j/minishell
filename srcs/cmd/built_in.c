/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:32:07 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/30 15:06:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 4) || !ft_strncmp("pwd", cmd, 3) || \
	!ft_strncmp("export", cmd, 6) || !ft_strncmp("unset", cmd, 5) || \
	!ft_strncmp("env", cmd, 3) || !ft_strncmp("exit", cmd, 4))
		return (1);
	return (0); 
}

int	exec_built_in(t_cmd *command)
{
	// 빌트인 명령 실행
	printf("I 'm %s\n", command->cmd);
	exit(1); // 무조건 있어야 함
	return (SUCCESS);
}