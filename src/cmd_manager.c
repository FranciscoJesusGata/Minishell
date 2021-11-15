/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:01:05 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/15 12:37:30 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	new_cmd(int argc, char **argv, t_simpleCmd **cmds)
{
	t_simpleCmd *new_cmd;
	t_simpleCmd *iter;

	new_cmd = (t_simpleCmd *)malloc(sizeof(t_simpleCmd));
	if (!new_cmd)
	{
		perror("Error: allocation error");
		exit(1);
	}
	new_cmd->argc = argc;
	new_cmd->argv = argv;
	new_cmd->nxt = NULL;
	if (!*cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	iter = *cmds;
	while (iter->nxt)
		iter = iter->nxt;
	iter->nxt = new_cmd;
}
