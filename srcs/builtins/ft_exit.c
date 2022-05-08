/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 17:39:09 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_exit(t_cmd *command)
{
	if (command->is_pipe)
		return ;
	if (!command->argv[1])
	{
		printf("exit\n");
		exit(127);
	}
	else if (!check_exit(command->argv[1]))
	{
		printf("exit\n");
		printf("soobash: exit: %s", command->argv[1]);
		printf(": numeric argument required\n");
		exit(255);
	}
	else if (command->argc > 2)
	{
		printf("soobash: exit: too many arguments\n");
		g_state.exit_status = 1;
		return ;
	}
}
