/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:57:42 by fgata-va          #+#    #+#             */
/*   Updated: 2021/05/31 12:51:09 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_command(t_term *term, char *command)
{
	free(term->h_cursor->replica);
	term->h_cursor->replica = ft_strdup(term->h_cursor->command);
	restore_position(&term->history);
	term->h_cursor = term->history;
	if (!term->h_cursor->prev ||
		(term->h_cursor->prev
		&& ft_strcmp(command, term->h_cursor->prev->command)))
		ft_dlst_prepend(term->h_cursor, ft_dlstnew(command));
}

void	navigate_history(t_term *term, int dir)
{
	int	i;
	int	len;

	if (ft_strcmp(term->h_cursor->replica, term->buffer))
	{
		free(term->h_cursor->replica);
		term->h_cursor->replica = ft_strdup(term->buffer);
	}
	if (dir && term->h_cursor->prev)
		term->h_cursor = term->h_cursor->prev;
	else if (!dir && term->h_cursor->next)
		term->h_cursor = term->h_cursor->next;
	else
	{
		sound_bell();
		return ;
	}
	clear_line(term);
	i = 0;
	len = ft_strlen(term->h_cursor->replica);
	while (i < len)
		write_buffer(&term->cursor, term->h_cursor->replica[i++]);
}

void	print_history(t_hist *history)
{
	t_hist	*current;
	int			i;

	i = 0;
	current = history;
	while (current->prev)
		current = current->prev;
	while (current->next)
	{
		printf("%d  %s\n", i + 1, current->command);
		current = current->next;
		i++;
	}
}
