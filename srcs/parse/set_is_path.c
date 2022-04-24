/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_is_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:50:09 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/25 00:50:29 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_is_path(t_cmd *cmd)
{
	int		i;
	t_cmd	*cur;

	i = -1;
	cur = cmd;
	while (cur)
	{
		if (cur->cmd[0] == '/')
			cur->is_path = 1;
		cur = cur->next;
	}
}
