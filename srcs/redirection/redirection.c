/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:29 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/28 03:11:46 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rdr_l(char *in)
{
	int	fd;

	fd = open(in, O_RDONLY);
	if (fd == ERROR)
		return (ERROR);
	if (dup2(fd, READ) == ERROR)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}

int	rdr_rr(t_redir *redir)
{
	int			fd;
	t_redir		*rdr;

	rdr = redir;
	while (rdr->next)
	{
		fd = open(rdr->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == ERROR)
			return (ERROR);
		close(fd);
		rdr = rdr->next;
	}
	fd = open(rdr->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == ERROR)
		return (ERROR);
	if (dup2(fd, WRITE) == ERROR)
		return (ERROR);
	close(fd);
	return (SUCCESS);
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
			break ;
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
	t_redir	*rdr;

	rdr = redir;
	while (rdr->next)
	{
		fd = open(rdr->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == ERROR)
			return (ERROR);
		close(fd);
		rdr = rdr->next;
	}
	fd = open(rdr->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == ERROR)
		return (ERROR);
	if (dup2(fd, WRITE) == ERROR)
		return (ERROR);
	close(fd);
	return (SUCCESS);
}

int	redirection_handler(t_cmd *command)
{
	if (command->input)
	{
		if (rdr_l(command->input->file_name) == ERROR)
			return (ERROR);
	}
	else if (command->output)
	{
		if (command->output->type == REDIR_R)
		{
			if (rdr_r(command->output) == ERROR)
				return (ERROR);
		}
		else if (command->output->type == REDIR_RR)
		{
			if (rdr_rr(command->output) == ERROR)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
