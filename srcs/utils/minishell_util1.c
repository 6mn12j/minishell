/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/23 01:42:18 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_twoptr_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	ft_strjoin_char(char **dst, char ch)
{
	char	str[2];
	char	*temp;

	temp = *dst;
	str[0] = ch;
	str[1] = '\0';
	*dst = ft_strjoin(*dst, str);
	free(temp);
}

int	count_pipe(char **commands)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (commands[i] != NULL)
	{
		if (ft_strncmp(commands[i], "|", 2) == 0)
			count++;
		i++;
	}
	return (count);
}
