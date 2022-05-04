/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/02 17:58:24 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *command)
{
	char	*cur_pwd;

	(void)command;
	cur_pwd = getcwd(0, _PC_PATH_MAX);
	printf("%s\n", cur_pwd);
	free(cur_pwd);
	cur_pwd = NULL;
	g_state.exit_status = 0;
	return ;
}
