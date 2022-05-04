/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 01:50:32 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/01 03:34:18 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_index(char *key)
{
	int		i;
	char	*temp;

	i = -1;
	temp = ft_strjoin(key, "=");
	while (g_state.envp[++i])
	{
		if (!ft_strncmp(temp, g_state.envp[i], ft_strlen(temp)))
		{
			free(temp);
			temp = NULL;
			return (i);
		}
	}
	free(temp);
	temp = NULL;
	return (i);
}

int	check_env_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (FALSE);
	else
		i++;
	while (key[i])
	{
		if (!ft_isalpha(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
