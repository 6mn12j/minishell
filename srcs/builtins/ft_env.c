/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 01:25:33 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *command)
{
	int	i;

	(void)command;
	i = -1;
	while (g_state.envp[++i])
	{
		if (ft_strchr(g_state.envp[i], '='))
			printf("%s\n", g_state.envp[i]);
	}
	g_state.exit_status = 0;
	return ;
}
