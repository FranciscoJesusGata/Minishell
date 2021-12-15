/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:51:58 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/15 14:49:29 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*launch_term(void)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	line = readline("\001\e[38;5;38m\002MiniShell ~ 👉  \001\e[0m\002");
	if (line && *line)
		add_history(line);
	else if (line && !*line)
		g_exit_code = 0;
	return (line);
}
