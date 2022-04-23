/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:16:28 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/23 02:36:20 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir_node(int type, char *file_name)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	node->type = type;
	node->file_name = file_name;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_redir_node(t_redir *new_node, t_redir *head)
{
	t_redir	*cur;

	cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	new_node->prev = cur;
	cur->next = new_node;
}

void	handle_redir(t_cmd *node, int type, char *file_name, int *i)
{
	if (file_name != NULL)
		(*i)++;
	if (type == REDIR_S_OUT)
	{
		if (node->output == NULL)
			node->output = create_redir_node(type, file_name);
		else
			add_redir_node(create_redir_node(type, file_name), node->output);
	}
	else if (type == REDIR_D_OUT)
	{
		if (node->output == NULL)
			node->output = create_redir_node(type, file_name);
		else
			add_redir_node(create_redir_node(type, file_name), node->output);
	}
	else if (type == REDIR_S_IN)
	{
		if (node->input == NULL)
			node->input = create_redir_node(type, file_name);
		else
			add_redir_node(create_redir_node(type, file_name), node->input);
	}
}
