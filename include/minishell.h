/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/22 17:20:42 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "../libft/libft.h"

# define READ 0
# define WRITE 1

typedef struct s_state
{
	char	**envp;
	int		exit_status;
}	t_state;

typedef struct s_redir {
	int				cnt; //갯수
	char			*file_name;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

/*
	pipe_type: 0 : 시작, 1: 중간, 2: 끝, 3: 혼자있을 때
*/
typedef struct s_cmd {
	int				pipe_type;
	char			*cmd;
	char			option;   //n
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct t_redir	*input;
	struct t_redir	*output;
	char			*heredoc; //종료문자
}	t_cmd;

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
