/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/25 00:41:21 by minjupar         ###   ########.fr       */
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
	if (!ft_strncmp(input, "\n", ft_strlen(input) + 1) || \
		space_cnt == (int)ft_strlen(input))
	{
		add_history(input);
		return (0);
	}
	if (!check_quote(input))
	{
		printf("Invalid quote\n");
		return (0);
	}
	return (1);
}

char	*read_input(char **input)
{
	*input = readline("soobash$:");
	return (*input);
}

void	excute_cmd(t_cmd *head)
{
	if (!head->next && head->cmd)
	{
		//빌트인 실행
	}
	else
	{
		//파이프 여러개 일때
	}
}

void	handle_prompt(void)
{
	char	*input;
	t_cmd	*head;

	while (read_input(&input))
	{
		if (!check_input(input))
		{
			free(input);
			input = NULL;
			continue ;
		}
		head = NULL;
		parser(&input, &head);
		excute_cmd(head);
		//실행에 head넘겨주기;
		//free head
		add_history(input);
		free(input);
		input = NULL;
	}
	ft_free_two_ptr(g_state.envp);
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
