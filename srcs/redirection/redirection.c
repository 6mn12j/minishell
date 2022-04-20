/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:29 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/20 14:52:58 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(char *in)
{
	int	fd;

	fd = open(in, O_RDONLY);
	dup2(fd, READ);
	close(fd);
}

void	redirect_out(char *out)
{
	int	fd;

	fd = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(fd, WRITE);
	close(fd);
}