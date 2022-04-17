/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 02:03:36 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *input)
{
	int		i;
	char	c;

	i = -1;
	c = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (c == 0)
				c = input[i];
			else if (c == '\'' && input[i] == '\'')
				c = 0;
			else if (c == '"' && input[i] == '"')
				c = 0;
			else if (c == '\'' && input[i] == '"')
				continue ;
			else if (c == '"' && input[i] == '\'')
				continue ;
		}
	}
	return (c == 0);
}

int	check_input(char *input)
{
	int	i;

	i = -1;
	if (!input)
		return (0);
	if (!check_quote(input))
	{
		printf("Invalid quote\n");
		return (0);
	}
	return (1);
}

char	*read_input(char **input)
{
	char	*temp;

	temp = get_env("PWD");
	*input = readline(ft_strjoin(temp, "/bash$:"));
	free(temp);
	return (*input);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*input;
	char	**command;

	(void)argc;
	(void)argv;
	(void)command;
	copy_env(envp);
	init_signal();
	while (read_input(&input))
	{
		if (!check_input(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		command = ft_split_command(input);
		free(input);
		//실행 넘겨주기
		//free command;
	}
	//free env
	return(1);
}
