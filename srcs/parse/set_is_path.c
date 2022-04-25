/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_is_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 03:19:21 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/25 15:23:21 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_is_path(t_cmd *cmd)
{
	//TODO: 상대경로는 ...? ~ -> /Users/username 으로 파싱됨

	int		i;
	t_cmd	*cur;

	i = -1;
	cur = cmd;
	while (cur)
	{
		if (cur->cmd[0] == '/')
			cur->is_path = 1;
		if (!ft_strncmp(cur->cmd, "..", 2))
			cur->is_path = 1;
		cur = cur->next;
	}
}
