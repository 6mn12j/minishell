/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:29 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/24 21:46:34 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(char *in) // <
{
	int	fd;

	fd = open(in, O_RDONLY);
	dup2(fd, READ);
	close(fd);
}

void	redirect_out(char *out) // >
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(fd, 1);
	close(fd);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	free(line);
}