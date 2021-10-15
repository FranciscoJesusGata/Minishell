/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 10:16:59 by fgata-va          #+#    #+#             */
/*   Updated: 2021/05/25 19:54:04 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_position(t_hist **history)
{
	while ((*history)->next)
		*history = (*history)->next;
}

void	free_history(t_hist *history)
{
	t_hist *current;
	t_hist *prev;

	restore_position(&history);
	current = history;
	while (current)
	{
		prev = current->prev;
		free(current->command);
		free(current->replica);
		free(current);
		current = prev;
	}
}

t_hist	*ft_dlstnew(char const *command)
{
	t_hist	*history;

	history = malloc(sizeof(t_hist));
	if (!history)
		return (NULL);
	history->command = ft_strdup(command);
	history->replica = ft_strdup(command);
	history->next = NULL;
	history->prev = NULL;
	return (history);
}

void	ft_dlst_prepend(t_hist *current, t_hist *new)
{
	t_hist	*prev;

	prev = current->prev;
	new->prev = prev;
	if (prev)
		prev->next = new;
	current->prev = new;
	new->next = current;
}

void	restore_original(t_hist *history)
{
	while (history)
	{
		if (ft_strncmp(history->command, history->replica,
			ft_strlen(history->command)))
		{
			free(history->replica);
			history->replica = history->command;
		}
		history = history->prev;
	}
}
