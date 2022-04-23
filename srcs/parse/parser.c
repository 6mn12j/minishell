/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/23 07:56:56 by minjupar         ###   ########.fr       */
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
		if (ft_strncmp(commands[i], "|", 2) == 0)
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

void	set_pipe_type(t_cmd	*cur)
{
	if (!cur->prev && !cur->next)
		cur->pipe_type = 0;
	else
	{
		cur->pipe_type = 1;
		cur = cur->next;
		while (cur)
		{
			if (cur->next)
				cur->pipe_type = 2;
			else if (!cur->next)
				cur->pipe_type = 3;
			cur = cur->next;
		}
	}
}

void	handle_heredoc(t_cmd *cur, char *heredoc, int *i)
{
	// TODO : heredoc 여러개일떄 처리할 것인지?
	if (!heredoc)
		return ;
	else
		(*i)++;
	if (cur->heredoc)
	{
		free(cur->heredoc);
		cur->heredoc = NULL;
	}
	cur->heredoc = heredoc;
}

void	set_cmd_list(char **commands, t_cmd	*cur, int i, int i_argv)
{
	while (commands[++i] && cur)
	{
		if (ft_strncmp(commands[i], "|", 2) == 0)
		{
			cur = cur->next;
			i_argv = 0;
		}
		else
		{
			if (ft_strncmp(commands[i], "<<", 3) == 0)
				handle_heredoc(cur, ft_strdup(commands[i + 1]), &i);
			else if (ft_strncmp(commands[i], "<", 2) == 0)
				handle_redir(cur, REDIR_S_IN, ft_strdup(commands[i + 1]), &i);
			else if (ft_strncmp(commands[i], ">>", 3) == 0)
				handle_redir(cur, REDIR_D_OUT, ft_strdup(commands[i + 1]), &i);
			else if (ft_strncmp(commands[i], ">", 2) == 0)
				handle_redir(cur, REDIR_S_OUT, ft_strdup(commands[i + 1]), &i);
			else
			{
				cur->argv[i_argv++] = ft_strdup(commands[i]);
				cur->cmd = cur->argv[0];
			}
		}
	}
}

void	set_cmd(char **commands, t_cmd **head)
{
	malloc_cmd_list(commands, head);
	malloc_argv(commands, head);
	set_cmd_list(commands, *head, -1, 0);
	set_pipe_type(*head);
}

void	parser(char **input, t_cmd **head)
{
	char	**commands;

	commands = parse_commands(ft_split_commands(*input));
	set_cmd(commands, head);
	print_test(head); // TODO : 내기 전에 삭제
	ft_free_two_ptr(commands);
}
