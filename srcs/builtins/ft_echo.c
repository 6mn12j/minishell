/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:01:09 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/30 19:42:47 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n_option(t_cmd *command, int j, char *option)
{
	int	i;

	if (command->argv[j][0] != '-')
		return (0);
	if (!ft_strncmp("-n", command->argv[j], 3))
	{
		*option = 'n';
		return (1);
	}
	i = 1;
	while (command->argv[j][i])
	{
		if (command->argv[j][i] != 'n')
			return (1);
		i++;
	}
	*option = 'n';
	return (1);
}

void	ft_echo(t_cmd *command)
{
	char	option;
	int		j;

	j = 0;
	option = 0;

	while (command->argv[++j])
	{
		while (check_n_option(command, j, &option))
			j++;
		printf("%s", command->argv[j]);
		if (command->argv[j + 1] != NULL)
			printf(" ");
	}
	if (option != 'n')
		printf("\n");
	return ;
}
