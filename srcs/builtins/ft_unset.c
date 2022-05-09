/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 17:39:11 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_error_printf(char *error_props)
{
	g_state.exit_status = 1;
	printf("bash: unset: `%s': not a valid identifier\n", error_props);
	g_state.exit_status = 1;
	return ;
}

void	unset_env(int index)
{
	char	**temp;
	int		i;
	int		j;

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

void	handle_unset(char *argv)
{
	int		index;

	if (!is_valid_env_key(argv))
		return (ft_unset_error_printf(argv));
	index = get_env_index(argv);
	if (index >= 0)
		unset_env(index);
}

void	ft_unset(t_cmd *command)
{
	int	i;

	i = 0;
	g_state.exit_status = 0;
	while (command->argv[++i])
		handle_unset(command->argv[i]);
}
