/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_is_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 03:19:21 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/27 02:56:37 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_is_path(t_cmd *cmd)
{
	int		i;
	t_cmd	*cur;

	i = -1;
	cur = cmd;
	if (!cur->cmd)
		return ;
	while (cur)
	{
		if (ft_strchr(cur->cmd, '/'))
			cur->is_path = 1;
		cur = cur->next;
	}
}
