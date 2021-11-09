/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:51:58 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/09 18:07:37 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*launch_term(void)
{
	char	*line;

	line = readline("\001\e[38;5;38m\002MiniShell ~ 👉  \001\e[0m\002");
	if (line && *line)
		add_history(line);
	return (line);
}
