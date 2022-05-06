/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/05 18:19:18 by jinyoo           ###   ########.fr       */
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

static int	check_newline_error(t_cmd *node)
{
	if ((node->here_filename && node->heredoc == NULL) || \
			(node->output && node->output->file_name == NULL) || \
			(node->input && node->input->file_name == NULL))
	{
		printf("soobash: syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	return (FALSE);
}

int	error_cmds(t_cmd *node)
{
	int	i;

	while (node)
	{
		if (node->cmd == NULL && node->input)
		{
			printf("No such file or directory\n");
			return (TRUE);
		}
		else if (node->cmd == NULL && node->is_pipe && node->input == NULL && node->output == NULL && node->heredoc == NULL)
		{
			printf("syntax error near unexpected token `|'\n");
			return (TRUE);
		}
		else if (check_newline_error(node))
			return (TRUE);
		i = 0;
		while (node->argv[i])
		{
			if (node->argv[i][0] == 7)
			{
				printf("soobash: ");
				printf("syntax error near unexpected token `newline'\n");
				return (TRUE);
			}
			i++;
		}
		node = node->next;
	}
	return (FALSE);
}

void	ft_error(void)
{
	write(STDERR_FILENO, "malloc error\n", 13);
	exit(-1);
}
