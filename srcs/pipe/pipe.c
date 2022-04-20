/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:50:53 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/20 14:51:17 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	use_pipe(int pipe_fd[2], int usage)
{
	dup2(pipe_fd[usage], usage);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}