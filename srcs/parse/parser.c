/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/30 18:29:11 by jinyoo           ###   ########.fr       */
=======
/*   Updated: 2022/05/03 23:39:39 by minjupar         ###   ########.fr       */
>>>>>>> 88adb52227fa62c35c24673db1ca1256aaeea340
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
		if (!cur->argv)
			return (ft_error());
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
	set_is_path(*head);
}

void	parser(char **input, t_cmd **head)
{
	char	**commands;

	*head = NULL;
	commands = parse_cmds(ft_split_cmds(*input));
	set_cmd(commands, head);
	ft_free_two_ptr(commands);
	return ;
}
