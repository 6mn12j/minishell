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
/*

1.카운트세서
	1. < > 3개 이상일때, | 2개 이상일때 ->
		 전역변수에 errono

*/

int	is_separate(char **temp, char *cmd, int *i)
{
	char	symbol;
	int		cnt;

	cnt = 0;
	if (cmd[*i] == '|' || cmd[*i] == '>' || cmd[*i] == '<')
		symbol = cmd[*i];
	else
		return (0);
	ft_strjoin_char(temp, 1);
	while (cmd[*i] == symbol)
	{
		ft_strjoin_char(temp, symbol);
		(*i)++;
		cnt++;
	}
	(*i)--;
	if ((symbol == '|' && cnt >= 2) || \
		(symbol != '|' && cnt >= 3))
		g_state.exit_status = WAIT_TIMEOUT;
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
		if (quote != '\'' && command[i] == '$')
			i = parse_env(temp, command, i);
		else if (command[i] == '~')
		{
			join_env(temp, "HOME");
			continue ;
		}
		else if (!quote && (command[i] == '\'' || command[i] == '"'))
			change_quote(command[i], &quote);
		else if (quote && command[i] == quote)
			change_quote(command[i], & quote);
		else if (!quote && is_separate(temp, command, &i))
			ft_strjoin_char(temp, 1);
		else
			ft_strjoin_char(temp, command[i]);
	}
	ft_strjoin_char(temp, 1);
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
	result = ft_split(temp, 1);
	free(temp);
	temp = NULL;
	return (result);
}
