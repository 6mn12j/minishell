/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/22 21:25:52 by jinyoo           ###   ########.fr       */
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
	int	space_cnt;

	i = -1;
	space_cnt = 0;
	if (!input)
		return (0);
	while (input[++i])
	{
		if (input[i] == ' ')
			space_cnt++;
	}
	if (!ft_strncmp(input, "\n", ft_strlen(input)) || \
		space_cnt == (int)ft_strlen(input))
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
	// temp = get_env("PATH");
	//*input = readline(ft_strjoin(temp, "/bash$:"));
	*input = readline("soobash$:");

	//free(temp);
	//temp = 0;
	return (*input);
}

void	handle_prompt(void)
{
	char	*input;
	char	**command;

	while (read_input(&input))
	{
		if (!check_input(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		command = ft_split_command(input);
		//parse_command(command);
		free(input);
		input = 0;
		//실행 넘겨주기
		//free command;
	}
	//free env
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	copy_env(envp);
	init_signal();
	handle_prompt();
	g_state.exit_status = 130;
	return (g_state.exit_status);
}
