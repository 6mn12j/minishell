/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/23 02:11:43 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_argv(char **commands, t_cmd **head)
{
	int		i;
	t_cmd	*cur;

	i = -1;
	cur = *head;
	while (commands[++i] != NULL && cur != NULL)
	{
		if (ft_strncmp(commands[i], "|", 2) == 0)
			cur = cur->next;
		else
			cur->argc++;
	}
	cur = *head;
	while (cur != NULL)
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
	if (cur->prev == NULL && cur->next == NULL)
		cur->pipe_type = 0;
	else
	{
		cur->pipe_type = 1;
		cur = cur->next;
		while (cur != NULL)
		{
			if (cur->next != NULL)
				cur->pipe_type = 2;
			else if (cur->next == NULL)
				cur->pipe_type = 3;
			cur = cur->next;
		}
	}
}

void	set_cmd_list(char **commands, t_cmd	*cur, int i, int i_argv)
{
	while (commands[++i] != NULL && cur != NULL)
	{
		if (ft_strncmp(commands[i], "|", 2) == 0)
		{
			cur = cur->next;
			i_argv = 0;
		}
		else
		{
			if (ft_strncmp(commands[i], "<<", 3) == 0)
			 	// TODO : heredoc 여러개일떄 처리할 것인지?
				cur->heredoc = ft_strdup(commands[++i]);
			else if (ft_strncmp(commands[i], "<", 2) == 0)
				handle_redir(cur, REDIR_SINGLE_IN, ft_strdup(commands[++i]));
			else if (ft_strncmp(commands[i], ">>", 3) == 0)
				handle_redir(cur, REDIR_DOUBLE_OUT, ft_strdup(commands[++i]));
			else if (ft_strncmp(commands[i], ">", 2) == 0)
				handle_redir(cur, REDIR_SINGLE_OUT, ft_strdup(commands[++i]));
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
	//set cmd //head에 commands담기.
	set_cmd(commands, head);

	printf("head : %p\n", *head);
	for (t_cmd *cur = *head; cur != NULL; cur = cur->next)
	{
		for (char **cur_arg = cur->argv; *cur_arg != NULL; cur_arg++)
			printf("argv : %s\n", *cur_arg);
		printf("input_head : %p\n", cur->input);
		for (t_redir *cur_in = cur->input; cur_in != NULL; cur_in = cur_in->next)
			printf("input : %s\n", cur_in->file_name);
		printf("output_head : %p\n", cur->output);
		for (t_redir *cur_out = cur->output; cur_out != NULL; cur_out = cur_out->next)
			printf("output[%d] : %s\n", cur_out->type, cur_out->file_name);
		printf("heredoc : %s\n", cur->heredoc);
	}
	// system("leaks minishell");
	ft_free_two_ptr(commands);
}
