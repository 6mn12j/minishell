/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 17:22:02 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_error_printf(char *error_props)
{
	printf("bash: unset: `%s': not a valid identifier\n", error_props);
	g_state.exit_status = 1;
	return ;
}

void	ft_unset(t_cmd *command)
{
	int		i;
	int		j;
	int		index;
	char	**temp;

	if (!check_env_key(command->argv[1]))
		return (ft_unset_error_printf(command->argv[1]));
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
	g_state.exit_status = 0;
}
