/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/24 15:58:10 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separate(char **temp, char *cmd, int *i)
{
	char	symbol;
	int		cnt;

	cnt = 0;
	if (cmd[*i] == '|' || cmd[*i] == '>' || cmd[*i] == '<')
		symbol = cmd[*i];
	else
		return (0);
	ft_strjoin_char(temp, SEPARATOR);
	while (cmd[(*i)] == symbol)
	{
		cnt++;
		(*i)++;
	}
	(*i)--;
	//printf("cmd: %c i:%d\n",cmd[*i],*i);
	if (cnt == 1 && symbol == '|')
		ft_strjoin_char(temp, PIPE_TYPE);
	else if (cnt == 1 && symbol == '<')
		ft_strjoin_char(temp, REDIR_L);
	else if (cnt == 1 && symbol == '>')
		ft_strjoin_char(temp, REDIR_R);
	else if (cnt == 2 && symbol == '<')
		ft_strjoin_char(temp, HEREDOC);
	else if (cnt == 2 && symbol == '>')
		ft_strjoin_char(temp, REDIR_RR);
	else
		ft_strjoin_char(temp, ERROR_TYPE);
	return (1);
}

void	parse_command(char **temp, char *command)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (command[++i])
	{
		if (quote != '\'' && command[i] == '$' && command[i + 1] != '\0')
			i = parse_env(temp, command, i);
		else if (!quote && command[i] == '~')
			join_env(temp, "HOME");
		else if (!quote && (command[i] == '\'' || command[i] == '"'))
			change_quote(command[i], &quote);
		else if (quote && command[i] == quote)
			change_quote(command[i], & quote);
		else if (!quote && is_separate(temp, command, &i))
			ft_strjoin_char(temp, SEPARATOR);
		else
			ft_strjoin_char(temp, command[i]);
	}
	ft_strjoin_char(temp, SEPARATOR);
}

char	**parse_cmds(char **commands)
{
	int		i;
	char	*temp;
	char	**result;

	i = -1;
	temp = ft_strdup("");
	while (commands[++i])
		parse_command(&temp, commands[i]);
	ft_free_two_ptr(commands);
	result = ft_split(temp, SEPARATOR);
	free(temp);
	temp = NULL;
	return (result);
}
