/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 02:32:04 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/29 02:35:24 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_heredoc_file(t_cmd *cur, char *heredoc)
{
	static int	index = 0;
	char		*filename;

	cur->heredoc = heredoc;
	if (cur->here_filename)
		filename = ft_strjoin(".temp", ft_itoa(index));
	else
		filename = ft_strjoin(".temp", ft_itoa(++index));
	cur->here_filename = filename;
	return ;
}


int	read_heredoc(t_cmd *cur, char *heredoc)
{
	int			fd;
	char		*line;

	make_heredoc_file(cur, heredoc);
	fd = open(cur->here_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc == NULL)
		return (0);
	line = readline("> ");
	while (line && ft_strncmp(line, heredoc, ft_strlen(line)))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("> ");
		if (line == NULL)
		{
			cur->here_filename = NULL;
			return (1);
		}
	}
	free(line);
	line = NULL;
	return (1);
}

int	handle_heredoc(t_cmd *cur, char *heredoc, int *i)
{
	if (read_heredoc(cur, heredoc))
	{
		if (cur->input == NULL)
		{
			handle_redir(cur, REDIR_L, ft_strdup(cur->here_filename), i);
			return (1);
		}
		else
			(*i)++;
	}
	return (1);
}
