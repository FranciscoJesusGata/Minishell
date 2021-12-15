/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:49:41 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/15 13:02:39 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int signo)
{
	char *buffer;

	buffer = rl_line_buffer;
	if (signo == SIGQUIT)
		printf("\001\e[38;5;38m\002MiniShell ~ 👉  \033[0;0m%s  \001\e[0m\002\e[2D\e[0K", buffer);
}

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		printf("\001\e[38;5;38m\002MiniShell ~ 👉  \033[0;0m%s  \001\e[0m\002\e[2D\e[0K\n", rl_line_buffer);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//void	handle_sigint(int sig)
//{
//	(void)sig;
//	write(1, "\n", 1);
//	rl_on_new_line();
//	rl_line_buffer[0] = '\0';
//	rl_point = 0;
//	rl_end = 0;
//	rl_redisplay();
//	return ;
//}

//void	handle_sigquit(int sig)
//{
//	(void)sig;
//	rl_on_new_line();
//	rl_redisplay();
//	return ;
//}
