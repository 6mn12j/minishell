/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/10 21:05:26 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_value(char *key, char *argv)
{
	int	start;
	int	len;

	start = ft_strlen(key);
	len = ft_strlen(argv);
	if (start + 1 == len)
		return (ft_strdup(""));
	else if (start + 1 > len)
		return (NULL);
	return (ft_substr(argv, start + 1, len));
}

void	printf_envp(void)
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
		printf("%s", key);
		if (ft_strchr(g_state.envp[i], '='))
			printf("=\"%s\"", value);
		printf("\n");
		free(key);
		key = NULL;
		free(value);
		value = NULL;
	}
	return ;
}
