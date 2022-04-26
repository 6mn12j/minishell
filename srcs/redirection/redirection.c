/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:29 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/26 15:09:24 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rdr_l(char *in)
{
	int fd;
	int	r_fd;

	r_fd = dup(READ);
	fd = open(in, O_RDONLY);
	dup2(fd, READ);
	close(fd);
	return (r_fd);
}

int	rdr_rr(t_redir *redir)
{
	int			fd;
	int			w_fd;
	t_redir		*rdr;

	w_fd = dup(WRITE);
	rdr = redir;
	while (rdr->next)
	{
		fd = open(rdr->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		close(fd);
		rdr = rdr->next;
	}
	fd = open(rdr->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	dup2(fd, WRITE);
	close(fd);
	return (w_fd);
}

int	rdr_ll(char *heredoc)
{
	int		fd;
	char	*line;
	int		r_fd;
	// int		idx;
	// int		filename;

	r_fd = dup(READ);
	// filename = "tmp" + "idx";
	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, heredoc, ft_strlen(heredoc)) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (ft_strncmp(line, heredoc, ft_strlen(heredoc)) == 0)
		free(line);
	// dup2(fd, READ);
	// close(fd);
	// unlink("tmp");
	// ctrl + D 처리되면 안됨
	return (r_fd);
}

int	rdr_r(t_redir *redir)
{
	int		fd;
	int		w_fd;
	t_redir		*rdr;

	w_fd = dup(WRITE);
	rdr = redir;
	while (rdr->next)
	{
		fd = open(rdr->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		close(fd);
		rdr = rdr->next;
	}
	fd = open(rdr->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(fd, WRITE);
	close(fd);
	return (w_fd);
}
