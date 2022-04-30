/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/29 16:00:03 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//echo 쉘 터미널 환경 설정값 받아서 임의로 수정가능.
// static void	echoctl_off(void)
// {
// 	struct termios	term;

// 	if (isatty(STDIN_FILENO))
// 	{
// 		tcgetattr(STDIN_FILENO, &term);
// 		term.c_lflag &= ~(ECHOCTL);
// 		tcsetattr(STDIN_FILENO, TCSANOW, &term);
// 	}
// 	else if (isatty(STDOUT_FILENO))
// 	{
// 		tcgetattr(STDOUT_FILENO, &term);
// 		term.c_lflag &= ~(ECHOCTL);
// 		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
// 	}
// 	else if (isatty(STDERR_FILENO))
// 	{
// 		tcgetattr(STDERR_FILENO, &term);
// 		term.c_lflag &= ~(ECHOCTL);
// 		tcsetattr(STDERR_FILENO, TCSANOW, &term);
// 	}
// 	return ;
// }

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_state.exit_status = 1;
	}
}

void	init_signal(void)
{
	//echoctl_off();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
