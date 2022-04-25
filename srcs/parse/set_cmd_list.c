/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:00:32 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/25 17:31:53 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_heredoc(t_cmd *cur, char *heredoc, int *i)
{
	if (!heredoc)
		return (1);
	else
		(*i)++;
	if (cur->heredoc)
	{
		free(cur->heredoc);
		cur->heredoc = NULL;
	}
	cur->heredoc = heredoc;
	return (1);
}

int	check_redir(t_cmd *cur, char **commands, int *i)
{
	if (ft_strncmp(commands[*i], "<<", 3) == 0)
		return (handle_heredoc(cur, ft_strdup(commands[*i + 1]), i));
	else if (ft_strncmp(commands[*i], "<", 2) == 0)
		return (handle_redir(cur, REDIR_S_IN, ft_strdup(commands[*i + 1]), i));
	else if (ft_strncmp(commands[*i], ">>", 3) == 0)
		return (handle_redir(cur, REDIR_D_OUT, ft_strdup(commands[*i + 1]), i));
	else if (ft_strncmp(commands[*i], ">", 2) == 0)
		return (handle_redir(cur, REDIR_S_OUT, ft_strdup(commands[*i + 1]), i));
	return (0);
}

void	set_cmd_list(char **commands, t_cmd	*cur, int i, int i_argv)
{
	while (commands[++i] && cur)
	{
		if (ft_strncmp(commands[i], "|", 2) == 0)
		{
			cur->pipe_type = 1;
			cur = cur->next;
			i_argv = 0;
		}
		else
		{
			if (check_redir(cur, commands, &i))
				;
			else
			{
				cur->argv[i_argv++] = ft_strdup(commands[i]);
				cur->cmd = cur->argv[0];
			}
		}
	}
}
