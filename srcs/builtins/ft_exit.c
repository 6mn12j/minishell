/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 15:54:38 by minjupar         ###   ########.fr       */
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
	if (command->argc > 2)
	{
		if (!check_exit(command->argv[1]))
		{
			printf("soobash: exit: %s", command->argv[1]);
			printf(": numeric argument required\n");
			return ;
		}
		printf("soobash: exit: too many arguments\n");
		return ;
	}
	if (command->argc == 2)
	{
		if (!check_exit(command->argv[1]))
		{
			printf("soobash: exit: %s", command->argv[1]);
			printf(": numeric argument required\n");
			return ;
		}
		g_state.exit_status = ft_atoi(command->argv[1]);
	}
	printf("exit\n");
	exit(g_state.exit_status);
}
