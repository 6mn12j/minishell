/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/22 22:18:30 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	'$HOME' -> $HOME
	"$HOME" -> /Users/dellimanjyu
	"   $HOME" ->    /Users/dellimanjyu
*/

static int	change_quote(char c)
{
	static char	flag = 0;

	if (c == '\'' || c == '"')
	{
		if (flag == 0)
		{
			flag = c;
			return (1);
		}
		if (c == '\'' && flag == '\'')
		{
			flag = 0;
			return (1);
		}
		else if (c == '"' && flag == '"')
		{
			flag = 0 ;
			return (1);
		}
	}
	return (c == flag);
}

int	parse_env(char **temp, char *command, int start)
{
	char	*key;
	char	*value;
	char	*parse_temp;

	key = get_env_key(command, start);
	value = get_env(key);
	parse_temp = *temp;
	*temp = ft_strjoin(*temp, value);
	start += ft_strlen(key);
	free(key);
	free(parse_temp);
	return (start);
}

void	parse_command(char **temp, char*command)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (command[++i])
	{
		if (quote != '\'' && command[i] == '$')
			i = parse_env(temp, command, i);
		else if (!quote && change_quote(command[i]))
			quote = command[i];
		else if (quote && change_quote(command[i]))
			quote = 0;
		else
			ft_strjoin_char(temp, command[i]);
	}
	ft_strjoin_char(temp, 1);
}

char	**parse_commands(char **commands)
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
	return (result);
}
