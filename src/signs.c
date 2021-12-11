/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:49:41 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/11 19:02:39 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int signo)
{
	char *buffer;

	buffer = rl_line_buffer;
	if (signo == SIGQUIT)
		printf("\001\e[38;5;38m\002MiniShell ~ 👉  \033[0;37m%s  \001\e[0m\002\e[2D\e[0K", buffer);
}

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		printf("\001\e[38;5;38m\002MiniShell ~ 👉  \033[0;37m%s  \001\e[0m\002\e[2D\e[0K\n", rl_line_buffer);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();

	}
}

