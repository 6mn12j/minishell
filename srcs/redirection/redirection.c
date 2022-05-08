/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:29 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/08 16:47:39 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	rdr_l_error(char *file_name)
{
	printf("soobash: %s: %s\n", file_name, strerror(2));
	g_state.exit_status = 1;
	return (ERROR);
}

int	rdr_l(t_redir *redir)
{
	int	fd;
	t_redir *rdr;

	rdr = redir;
	while (rdr->next)
	{
		fd = open(rdr->file_name, O_RDONLY);
		if (fd == ERROR)
			return (rdr_l_error(rdr->file_name));
		close(fd);
		rdr = rdr->next;
	}
	fd = open(rdr->file_name, O_RDONLY);
	if (fd == ERROR)
		return (rdr_l_error(rdr->file_name));
	else
	{
		if (dup2(fd, READ) == ERROR)
			return (ERROR);
		close(fd);
	}
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
	int	w_fd;
	int	r_fd;

	w_fd = dup(WRITE);
	r_fd = dup(READ);
	if (command->input)
	{
		if (rdr_l(command->input) == ERROR)
			return (ERROR);
	}
	if (command->output)
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
