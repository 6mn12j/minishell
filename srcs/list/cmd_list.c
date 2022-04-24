/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:16:57 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/24 21:10:38 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd_node(t_cmd *prev)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		ft_error();
	node->pipe_type = 0;
	node->is_path = 0;
	node->cmd = NULL;
	node->argv = NULL;
	node->argc = 0;
	node->input = NULL;
	node->output = NULL;
	node->heredoc = NULL;
	node->next = NULL;
	node->prev = prev;
	return (node);
}

void	malloc_cmd_list(char **commands, t_cmd **head)
{
	t_cmd	*node;
	t_cmd	*prev;
	int		count;

	prev = NULL;
	count = count_pipe(commands);
	while (count >= 0)
	{
		node = create_cmd_node(prev);
		if (!*head)
			*head = node;
		if (prev)
			prev->next = node;
		prev = node;
		count--;
	}
}
