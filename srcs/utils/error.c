/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 23:44:00 by minjupar         ###   ########.fr       */
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
		ft_putendl_fd("soobash: syntax error near unexpected token `newline'", STDERR_FILENO);
		return (TRUE);
	}
	return (FALSE);
}

int	error_cmds(t_cmd *node)
{
	int	i;

	while (node)
	{
		if (node->argc == 2 && node->cmd == NULL && node->input)
			return (TRUE);
		else if (node->cmd == NULL && node->is_pipe && node->input == NULL && node->output == NULL && node->heredoc == NULL)
		{
			ft_putendl_fd("soobash: syntax error near unexpected token `|'", STDERR_FILENO);
			return (TRUE);
		}
		else if (check_newline_error(node))
			return (TRUE);
		i = 0;
		while (node->argv[i])
		{
			if (node->argv[i][0] == 7)
			{
				ft_putendl_fd("soobash: syntax error near unexpected token `newline'", STDERR_FILENO);
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
	ft_putendl_fd("MALLOC ERROR", STDERR_FILENO);
	exit(1);
}

int	invalid_cmd_error(char *cmd, char *path)
{
	ft_putstr_fd("soobash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("command not found", STDERR_FILENO);
	g_state.exit_status = 127;
	free(path);
	path = NULL;
	return (ERROR);
}
