/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/20 14:54:22 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "../libft/libft.h"

# define READ 0
# define WRITE 1

typedef struct s_state
{
	char	**envp;
	int		exit_status;
}	t_state;

/*global*/
t_state	g_state;

char	*get_env(char *key);
void	copy_env(char **envp);
void	init_signal(void);
int		ft_twoptr_len(char **envp);
void	ft_error(void);
char	**ft_split_command(char *str);

// pipe
void	use_pipe(int pipe_fd[2], int usage);

// redirection
void	redirect_in(char *in);
void	redirect_out(char *out);

#endif
