/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/01 03:34:18 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *command)
{
	int		i;
	int		j;
	int		index;
	char	**temp;

	if (!check_env_key(command->argv[1]))
	{
		printf("bash: unset: `%s': not a valid identifier\n",command->argv[1]);
		return ;
	}
	index = get_env_index(command->argv[1]);
	temp = (char **)malloc(sizeof(char *) * ft_twoptr_len(g_state.envp));
	if (!temp)
		return (ft_error());
	i = -1;
	j = -1;
	while (g_state.envp[++i])
	{
		if (i != index)
			temp[++j] = g_state.envp[i];
	}
	temp[j] = NULL;
	free(g_state.envp[index]);
	free(g_state.envp);
	g_state.envp = temp;
}
