/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:49:41 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 23:53:34 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int signo)
{
	if (signo == SIGQUIT)
	{
		printf("\001\e[38;5;38m\002MiniShell ~ 👉  \033[0;0m%s  ", rl_line_buffer);
		printf("\001\e[0m\002\e[2D\e[0K");
	}
}

void	handle_heredoc(int signo)
{
	(void)signo;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_struct.interrupted = 1;
}

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_struct.exit_code = 1;
	}
}
