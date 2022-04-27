/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/28 02:48:07 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_argv(char **commands, t_cmd **head)
{
	int		i;
	t_cmd	*cur;

	i = -1;
	cur = *head;
	while (commands[++i] && cur)
	{
		if (commands[i][0] == PIPE_TYPE)
			cur = cur->next;
		else
			cur->argc++;
	}
	cur = *head;
	while (cur)
	{
		cur->argv = (char **)malloc(sizeof(char *) * (cur->argc + 1));
		i = -1;
		while (++i <= cur->argc)
			cur->argv[i] = NULL;
		cur = cur->next;
	}
}

void	set_cmd(char **commands, t_cmd **head)
{
	malloc_cmd_list(commands, head);
	malloc_argv(commands, head);
	set_cmd_list(commands, *head, -1, 0);
}

void	parser(char **input, t_cmd **head)
{
	char	**commands;

	*head = NULL;
	commands = parse_cmds(ft_split_cmds(*input));
	set_cmd(commands, head);
	print_test(head); // TODO : 내기 전에 삭제
	ft_free_two_ptr(commands);
	return ;
}
