/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:32:03 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/14 12:23:22 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(int exit_code)
{
	ft_putstr_fd("\e[38;5;38mMiniShell ~ \e[0m", 1);
	if (!exit_code)
		ft_putstr_fd("👉 ", 1);
	else
		ft_putstr_fd("👎 ", 1);
}

void	sound_bell(void)
{
	tputs(tgetstr("bl", NULL), 1, ft_putchar);
}

void	clean_screen(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
}

void	welcome(void)
{
	ft_putstr_fd("\e[38;5;38m", 1);
	ft_putstr_fd("********************************************************",1);
	ft_putstr_fd("****************************************************\n", 1);
	ft_putstr_fd("*                                                       ", 1);
	ft_putstr_fd("                                                   *\n", 1);
	ft_putstr_fd("*         :::   :::   ::::::::::: ::::    ::: ::::::::::", 1);
	ft_putstr_fd(": ::::::::  :::    ::: :::::::::: :::        :::   *\n", 1);
	ft_putstr_fd("*       :+:+: :+:+:      :+:     :+:+:   :+:     :+:    ", 1);
	ft_putstr_fd(":+:    :+: :+:    :+: :+:        :+:        :+:    *\n", 1);
	ft_putstr_fd("*     +:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+   ", 1);
	ft_putstr_fd(" +:+        +:+    +:+ +:+        +:+        +:+     *\n", 1);
	ft_putstr_fd("*    +#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    ", 1);
	ft_putstr_fd("+#++:++#++ +#++:++#++ +#++:++#   +#+        +#+      *\n", 1);
	ft_putstr_fd("*   +#+       +#+     +#+     +#+  +#+#+#     +#+     ", 1);
	ft_putstr_fd("      +#+ +#+    +#+ +#+        +#+        +#+       *\n", 1);
	ft_putstr_fd("*  #+#       #+#     #+#     #+#   #+#+#     #+#    #+", 1);
	ft_putstr_fd("#    #+# #+#    #+# #+#        #+#        #+#        *\n", 1);
	ft_putstr_fd("* ###       ### ########### ###    #### ########### ##", 1);
	ft_putstr_fd("######  ###    ### ########## ########## ##########  *\n", 1);
	ft_putstr_fd("*                                                     ", 1);
	ft_putstr_fd("                                                     *\n", 1);
	ft_putstr_fd("********************************************************", 1);
	ft_putstr_fd("****************************************************\n", 1);
	ft_putstr_fd("\e[48;5;38m\e[37;1mBy: @fportalo && ", 1);
	ft_putstr_fd("@fgata-va\e[0m\n", 1);
}

void	clear_line(t_term *term)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, 15), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	term->cursor = term->buffer;
	*term->cursor = 0;
}
