/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/22 22:07:04 by minjupar         ###   ########.fr       */
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

# include "../libft/libft.h"

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
	pipe_type: 0 : 혼자있을 때, 1 : 시작, 2: 중간, 3: 끝
*/
typedef struct s_cmd {
	int				pipe_type;
	char			*cmd;
	char			**argv;   //
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct t_redir	*input;
	struct t_redir	*output;
	char			*heredoc; //종료문자
}	t_cmd;

/*global*/
t_state g_state;

char	*get_env(char *key);
void	copy_env(char **envp);
char	*get_env_key(char *command, int start);
void	init_signal(void);
int		ft_twoptr_len(char **envp);
void	ft_strjoin_char(char **dst, char ch);
void	ft_error(void);

void	parser(char **input, t_cmd **head);
char	**parse_commands(char **commands);
char	**ft_split_commands(char *str);
void	ft_free_two_ptr(char **ptr);

#endif
