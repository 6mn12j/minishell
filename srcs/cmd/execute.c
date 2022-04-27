/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:55:40 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/27 13:51:30 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_cmd(char *cmd, char *path)
{
	char		*tmp;
	char		*cmd_path;
	char		**env_paths;
	int			i;
	struct stat	buf;

	i = -1;
	env_paths = ft_split(path, ':');
	while (env_paths[++i])
	{
		tmp = ft_strjoin(env_paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(cmd_path, &buf) == 0)
			return (cmd_path);
	}
	return (NULL);
}

int	exec_one_cmd(t_cmd *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (!pid)
	{
		if (command->input)
			rdr_l(command->input->file_name);
		else if (command->output)
		{
			if (command->output->type == 1)
				rdr_r(command->output);
			else if (command->output->type == 2)
				rdr_rr(command->output);
		}
		execve(command->cmd, command->argv, g_state.envp);
	}
	else
		waitpid(pid, NULL, 0);
	return (1);
}

void	execute_cmd(t_cmd *command)
{
	char	*path;
	int		flag;

	path = get_env("PATH");
	if (!command->next && command->cmd)
	{
		//빌트인 실행

		//  ---------빌트인이 아닌 명령어 실행------------
		if (!command->is_path)
		{
			command->cmd = get_valid_cmd(command->cmd, path);
			flag = 1;
			// if (!command->cmd)
			// 	error
		}
		exec_one_cmd(command);
		// ----------------------------------------
	}
	else
	{
		//파이프 여러개 일때
	}
	if (flag)
		free(command->cmd);
}

