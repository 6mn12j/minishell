/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:16:57 by minjupar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/30 17:45:49 by jinyoo           ###   ########.fr       */
=======
/*   Updated: 2022/05/03 23:42:00 by minjupar         ###   ########.fr       */
>>>>>>> 88adb52227fa62c35c24673db1ca1256aaeea340
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_filename(t_cmd *head)
{
	int	result;

	result = 0;
	while (head)
	{
		head = head->next;
		result ++;
	}
	return (result);
}

t_cmd	*create_cmd_node(t_cmd *prev)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->is_pipe = 0;
	node->is_path = 0;
	node->cmd = NULL;
	node->argv = NULL;
	node->argc = 0;
	node->input = NULL;
	node->output = NULL;
	node->heredoc = NULL;
	node->here_filename = NULL;
	node->prog_path = getcwd(NULL, 0);
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

void	delete_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;
	t_cmd	*del_node;

	temp = *cmd;
	while (temp)
	{
		if (temp->here_filename)
			unlink(temp->here_filename);
		free(temp->here_filename);
		free(temp->heredoc);
		del_node = temp;
		temp = temp->next;
		ft_free_two_ptr(del_node->argv);
		if (del_node->input)
			delete_redir_list(del_node->input);
		if (del_node->output)
			delete_redir_list(del_node->output);
		free(del_node);
		del_node = NULL;
	}
	return ;
}
