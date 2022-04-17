/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/17 16:28:46 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **envp)
{
	int	i;

	i = -1;
	ft_twoptr_len(envp);
	g_state.envp = (char **)malloc(sizeof(char *) * ft_twoptr_len(envp) + 1);
	while (envp[++i])
		g_state.envp[i] = ft_strdup(envp[i]);
	return ;
}

char	*get_env(char *key)
{
	int		i;

	i = -1;
	while (g_state.envp[++i])
	{
		if (!ft_strncmp(g_state.envp[i], key, ft_strlen(key)))
			return (ft_substr(g_state.envp[i], ft_strlen(key) + 1, \
				ft_strlen(g_state.envp[i]) - ft_strlen(key) + 1));
	}
	return (ft_strdup(""));
}
