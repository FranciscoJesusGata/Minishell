/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_management_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:49:30 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/19 22:52:49 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_simpleCmd *cmds)
{
	int	pipe_fds[2];

	if ((pipe(pipe_fds)) < 0)
		exit(minishell_perror(1, "pipe error", NULL));
	cmds->fds[WRITE_END] = pipe_fds[WRITE_END];
	cmds->nxt->fds[READ_END] = pipe_fds[READ_END];
	cmds->nxt->prev = cmds->fds;
}

int	redirections(t_redir *redirections, int *fds, char **env)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (!open_files(redirections, &in, &out, env))
		return (0);
	link_fds(fds, in, READ_END);
	link_fds(fds, out, WRITE_END);
	return (1);
}
