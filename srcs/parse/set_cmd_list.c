/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:00:32 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/28 00:04:03 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(t_cmd *cur, char *heredoc)
{
	int			fd;
	char		*line;
	char		*filename;
	static int	index = 0;

	printf("heredoc:%s\n",heredoc);
	if (cur->here_filename)
		filename = ft_strjoin(".temp", ft_itoa(index));
	else
		filename = ft_strjoin(".temp", ft_itoa(++index));
	cur->here_filename = filename;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc == NULL)
		return (0);
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, heredoc, ft_strlen(line)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (ft_strncmp(line, heredoc, ft_strlen(line)) == 0)
		free(line);
	return (1);
}

int	handle_heredoc(t_cmd *cur, char *heredoc, int *i)
{

	if (read_heredoc(cur, heredoc))
		handle_redir(cur, REDIR_S_IN, cur->here_filename, i);
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
			cur->is_pipe = 1;
			cur->pipe[0] = 0;
			cur->pipe[1] = 0;
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
