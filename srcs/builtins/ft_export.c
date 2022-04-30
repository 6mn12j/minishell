/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/01 02:48:58 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printf_envp(void)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (g_state.envp[++i])
	{
		key = get_env_key(g_state.envp[i], 0);
		value = get_env(key);
		printf("declare -x ");
		printf("%s=", key);
		printf("\"%s\"\n", value);
		free(key);
		free(value);
	}
	return ;
}

char	*get_new_value(char *key, t_cmd *command)
{
	int	start;
	int	len;

	start = ft_strlen(key) + 1;
	len = ft_strlen(command->argv[1]);
	return (ft_substr(command->argv[1], start - 1, len));
}

void	update_env(char *key, char *new_value)
{
	int		index;
	char	*new_env_value;

	index = get_env_index(key);
	free(g_state.envp[index]);
	g_state.envp[index] = NULL;
	new_env_value = ft_strjoin(key, new_value);
	g_state.envp[index] = ft_strdup(new_env_value);
	free(new_env_value);
	new_env_value = NULL;
	return ;
}

void	set_new_env(char *key, char *new_value)
{
	int		i;
	int		len;
	char	**temp;

	len = ft_twoptr_len(g_state.envp) + 2;
	temp = g_state.envp;
	temp = (char **)malloc(sizeof(char *) * len);
	if (!temp)
	{
		ft_error();
		return ;
	}
	i = -1;
	while (g_state.envp[++i])
		temp[i] = g_state.envp[i];
	temp[i++] = ft_strjoin(key, new_value);
	temp[i] = NULL;
	ft_free_two_ptr(g_state.envp);
	g_state.envp = temp;
	return ;
}

void	ft_export(t_cmd *command)
{
	char	*key;
	char	*value;
	char	*new_value;

	if (command->argc == 1)
		return (printf_envp());
	key = get_env_key(command->argv[1], 0);
	value = get_env(key);
	new_value = get_new_value(key, command);
	if (!check_key(key))
	{
		printf("bash: export: `%s%s': not a valid identifier\n", key, new_value);
		return ;
	}
	if (ft_strlen(value) > 0)
		update_env(key, new_value);
	else
		set_new_env(key, new_value);
	return ;
}
