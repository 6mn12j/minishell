/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:55:40 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/30 15:15:37 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_cmd(t_cmd *command, char **env_paths)
{
	char		*tmp;
	char		*cmd_path;
	struct stat	buf;

	if (command->is_path)
	{
		if (stat(command->cmd, &buf) == 0)
			return (command->cmd);
	}
	else
	{
		while (*env_paths)
		{
			tmp = ft_strjoin(*env_paths, "/");
			cmd_path = ft_strjoin(tmp, command->cmd);
			free(tmp);
			if (stat(cmd_path, &buf) == 0)
				return (cmd_path);
			env_paths++;
		}
	}
	return (NULL);
}

static int	child_handler(t_cmd *command, int flag)
{
	if (command->input || command->output)
	{
		if (redirection_handler(command) == ERROR)
			return (ERROR);
	}
	if (command->is_pipe)
	{
		if (dup2(command->pipe[WRITE], WRITE) == ERROR)
			return (ERROR);
	}
	if (command->prev && command->prev->is_pipe)
	{
		if (dup2(command->prev->pipe[READ], READ) == ERROR)
			return (ERROR);
	}
	if (flag)
		exec_built_in(command);
	else
	{
		if (execve(command->cmd, command->argv, g_state.envp) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

static void	parent_handler(t_cmd *command, pid_t pid, int pipe_open)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	if (pipe_open)
	{
		close(command->pipe[WRITE]);
		if (!command->next)
			close(command->pipe[READ]);
	}
	if (command->prev && command->prev->is_pipe)
		close(command->prev->pipe[READ]);
	init_signal();
}

static int	exec_cmd(t_cmd *command, int flag)
{
	pid_t	pid;
	int		pipe_open;

	pipe_open = 0;
	if (command->is_pipe || (command->prev && command->prev->is_pipe))
	{
		pipe_open = 1;
		pipe(command->pipe);
	}
	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (!pid)
	{
		if (child_handler(command, flag) == ERROR)
			return (ERROR);
	}
	else
		parent_handler(command, pid, pipe_open);
	return (SUCCESS);
}

int	execute_cmds(t_cmd *command)
{
	char	*path;
	int		flag;
	
	path = get_env("PATH");
	while (command)
	{
		flag = 0;
		if (is_built_in(command->cmd))
			flag = 1;
		else if (command->cmd)
			command->cmd = get_valid_cmd(command, ft_split(path, ':'));
		if (!command->cmd)
			return (ERROR);
		exec_cmd(command, flag);
		if (!command->is_path && !flag)
			free(command->cmd);
		command = command->next;
	}
	return (SUCCESS);
}
