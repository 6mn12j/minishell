/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:55:40 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/09 17:47:03 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_cmd(t_cmd *command, char **env_paths)
{
	char		*tmp;
	char		*cmd_path;
	struct stat	buf;

	if (stat(command->cmd, &buf) == 0)
		return (command->cmd);
	else
	{
		while (*env_paths)
		{
			tmp = ft_strjoin(*env_paths, "/");
			cmd_path = ft_strjoin(tmp, command->cmd);
			free(tmp);
			tmp = NULL;
			if (stat(cmd_path, &buf) == 0)
				return (cmd_path);
			env_paths++;
		}
		free(cmd_path);
		cmd_path = NULL;
	}
	return (NULL);
}

static int	child_handler(t_cmd *command, int flag)
{
	signal(SIGQUIT, SIG_DFL);
	if (command->input || command->output)
	{
		if (redirection_handler(command) == ERROR)
			return (ERROR);
	}
	if (command->is_pipe && !command->output)
	{
		if (dup2(command->pipe[WRITE], WRITE) == ERROR)
			return (ERROR);
	}
	if (command->prev && command->prev->is_pipe && !command->input)
	{
		if (dup2(command->prev->pipe[READ], READ) == ERROR)
			return (ERROR);
	}
	if (flag)
		exec_built_in(command, flag);
	else
	{
		if (execve(command->cmd, command->argv, g_state.envp) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

void	parent_handler(t_cmd *command, pid_t pid, int pipe_open)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (status == SIGINT)
		printf("\n");
	else if (status == SIGQUIT)
		printf("Quit: %d\n", status);
	if (pipe_open)
	{
		close(command->pipe[WRITE]);
		if (!command->next)
			close(command->pipe[READ]);
	}
	if (command->prev && command->prev->is_pipe)
		close(command->prev->pipe[READ]);
	init_signal();
	g_state.exit_status = *(int *)&status >> 8 & 0x000000ff;
}

static int	exec_cmd(t_cmd *command, int flag)
{
	pid_t	pid;
	int		pipe_open;

	if (use_pipe(command, &pipe_open) == ERROR)
		return (ERROR);
	if (flag && !pipe_open)
	{
		if (exec_built_in_hanlder(command) == ERROR)
			return (ERROR);
	}
	else
	{
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
	}
	return (SUCCESS);
}

int	execute_cmds(t_cmd *command)
{
	char	*path;
	char	*cmd_cpy;

	path = get_env("PATH");
	while (command)
	{
		cmd_cpy = command->cmd;
		if (!is_built_in(command->cmd))
		{
			command->cmd = get_valid_cmd(command, ft_split(path, ':'));
			if (!command->cmd)
				return (invalid_cmd_error(cmd_cpy, path));
		}
		exec_cmd(command, is_built_in(command->cmd));
		if (!command->is_path && !is_built_in(command->cmd))
		{
			free(command->cmd);
			command->cmd = NULL;
		}
		command = command->next;
		if (command && !command->cmd)
			break;
	}
	free(path);
	path = NULL;
	return (SUCCESS);
}
