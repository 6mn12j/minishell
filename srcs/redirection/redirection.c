/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:29 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/25 17:53:57 by jinyoo           ###   ########.fr       */
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

int	rdr_r(char *out, int flag)
{
	int		fd;
	int		w_fd;

	(void)flag;
	w_fd = dup(WRITE);
	fd = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(fd, WRITE);
	return (w_fd);
}

int	rdr_rr(char *out, int flag)
{
	int		fd;
	int		w_fd;

	(void)flag;
	w_fd = dup(WRITE);
	fd = open(out, O_WRONLY | O_APPEND | O_CREAT, 0644);
	dup2(fd, WRITE);
	return (w_fd);
}
