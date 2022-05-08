/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 01:25:47 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **envp)
{
	int	i;

	i = -1;
	g_state.envp = (char **)malloc(sizeof(char *) * (ft_twoptr_len(envp) + 1));
	if (!g_state.envp)
		return (ft_error());
	while (envp[++i])
		g_state.envp[i] = ft_strdup(envp[i]);
	g_state.envp[i] = NULL;
	return ;
}

char	*get_env_key(char *command, int start)
{
	int		i;
	int		len;
	char	*key;

	len = 0;
	i = start;
	while (command[i] == '"' || command[i] == '$')
	{
		i++;
		start++;
	}
	while (command[++i])
	{
		if (command[i] == '\'' || command[i] == '"'\
		|| command[i] == ' ' || command[i] == '$' \
		|| command[i] == '|' || command[i] == '.' \
		|| command[i] == '=')
			break ;
		len++;
	}
	key = ft_substr(command, start, len + 1);
	return (key);
}

char	*get_env(char *key)
{
	int		i;
	char	*temp;

	i = -1;
	if (ft_strlen(key) == 0)
		return (ft_strdup(""));
	if (!ft_strncmp(key, "?", ft_strlen(key)))
		return (ft_itoa(g_state.exit_status));
	temp = ft_strjoin(key, "=");
	while (g_state.envp[++i])
	{
		if (!ft_strncmp(g_state.envp[i], temp, ft_strlen(temp)))
		{
			free(temp);
			return (ft_substr(g_state.envp[i], ft_strlen(key) + 1, \
				ft_strlen(g_state.envp[i]) - ft_strlen(key) + 1));
		}
	}
	free(temp);
	return (ft_strdup(""));
}

void	join_env(char **temp, char *key)
{
	char	*value;
	char	*parse_temp;

	value = get_env(key);
	parse_temp = *temp;
	*temp = ft_strjoin(*temp, value);
	free(value);
	free(parse_temp);
	key = NULL;
	parse_temp = NULL;
	return ;
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
	free(value);
	free(parse_temp);
	key = NULL;
	parse_temp = NULL;
	return (start);
}
