/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/28 00:04:42 by minjupar         ###   ########.fr       */
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

# include <fcntl.h>
# include <sys/stat.h>

# include "../libft/libft.h"
# include "../get_next_line/include/get_next_line.h"

# define READ 0
# define WRITE 1

# define WAIT_TIMEOUT 258

# define ERROR -1
# define SUCCESS 1

typedef struct s_state
{
	char	**envp;
	int		exit_status;
}	t_state;

# define REDIR_S_IN 0
# define REDIR_S_OUT 1
# define REDIR_D_OUT 2

typedef struct s_redir {
	int				type;
	char			*file_name;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd {
	int				is_pipe;
	int				is_path;
	int				pipe[2];
	char			*cmd;
	char			**argv;
	int				argc;
	struct s_redir	*input;
	struct s_redir	*output;
	char			*here_filename;
	//char			*heredoc;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

/*global*/
t_state	g_state;

/*parser*/
char	**ft_split_cmds(char *str);
char	**parse_cmds(char **commands);
void	set_is_path(t_cmd *cmd);
int		change_quote(char c, char *flag);
int		handle_heredoc(t_cmd *cur, char *heredoc, int *i);
int		check_redir(t_cmd *cur, char **commands, int *i);
void	set_cmd_list(char **commands, t_cmd	*cur, int i, int i_argv);
void	make_file(char *filename);
void	ft_free_two_ptr(char **ptr);
void	parser(char **input, t_cmd **head);
int		error_cmds(t_cmd *node);

void	print_test(t_cmd **head);// TODO: 내기 전에 삭제

/*env*/
void	copy_env(char **envp);
void	join_env(char **temp, char *key);
char	*get_env(char *key);
char	*get_env_key(char *command, int start);
int		parse_env(char **temp, char *command, int start);

void	init_signal(void);
int		ft_twoptr_len(char **twoptr);
int		count_pipe(char **commands);
void	ft_strjoin_char(char **dst, char ch);
void	ft_error(void);

// redirection
int		rdr_l(char *in);
int		rdr_r(t_redir *redir);
int		rdr_rr(t_redir *redir);
int		redirection_handler(t_cmd *command);

// execute
char	*get_valid_cmd(t_cmd *command, char **env_paths);
int		execute_cmds(t_cmd *command);

/*cmd list*/
t_cmd	*create_cmd_node(t_cmd *prev);
void	delete_cmd_list(t_cmd **cmd);
void	malloc_cmd_list(char **commands, t_cmd **head);

/*redir list*/
t_redir	*create_redir_node(int type, char *file_name);
void	delete_redir_list(t_redir *redir);
void	add_redir_node(t_redir *new_node, t_redir *head);
int		handle_redir(t_cmd *node, int type, char *file_name, int *i);
#endif
