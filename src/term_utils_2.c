/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:39:35 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/15 13:09:01 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_buffer(char **buffer, char input)
{
	write(1, &input, 1);
	**buffer = input;
	*buffer += 1;
	*(*buffer) = 0;
}

/*void	delete_buffer(char **buffer)
{
	*buffer -= 1;
	**buffer = 0;
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
}*/
