/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:27:56 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/20 00:21:57 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	deactivate_echo_ctl(void)
{
	struct termios	new_attr;

	new_attr = g_struct.term_attr;
	new_attr.c_lflag = ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_attr);
}
