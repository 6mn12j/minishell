/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/27 13:31:42 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1.cmd 가 NULL ex:"< a"
	2.heredoc이 NULL 일때  ex:"cat <<"
	3.output_head , input_head 값이 있는데 각 file_name이 null일때 ex:"cat <", "cat >"
	argv
		1. '<', '>' 3개 이상일때
		2. '|' 2개 이상일때
*/
int	error_cmds(t_cmd *node)
{
	while (node)
	{
		if (node->cmd == NULL)
			return (1);
		else if (g_state.exit_status == WAIT_TIMEOUT)
			return (1);
		// else if (node->here_filename && !node->input)
		// 	return (1);
		// else if ((node->output && node->output->file_name == NULL) \
		// || (node->input && node->input->file_name == NULL))
		// 	return (1);
		node = node->next;
	}
	return (0);
}

void	ft_error(void)
{
	printf("error\n");
	exit(1);
}
