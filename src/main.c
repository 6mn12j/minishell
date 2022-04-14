/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/15 05:50:52 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_state.exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b\a");
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	*str;
	char	*temp;

	(void)argc;
	(void)argv;
	g_state.exit_status = 0;
	copy_env(envp);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		temp = get_env("PWD");
		str = readline(ft_strjoin(temp, "/bash$:"));
		free(temp);
		if (str)
			printf("%s\n", str);
		else
			break ;
		add_history(str);
		free(str);
	}
}
