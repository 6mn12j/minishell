/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:55:40 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/27 04:49:18 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmds(t_cmd *node)
{
	while (node)
	{
		if (!node->next && node->cmd)
		{
			//빌트인 실행

			if (node->is_path) //절대,상대 경로 일때 테스트
			{
				int pid = fork();
				if (pid == 0)
				{
					execve(node->cmd,node->argv,g_state.envp);
					exit(1);
				}
				else
					wait(0);
			}
			else
			{
				//파이프 여러개 일때
			}
				node = node->next;
			}
		}

}
