/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:41:10 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/19 22:52:39 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_fds(t_simpleCmd *cmd)
{
	if (cmd->prev)
		close(cmd->prev[WRITE_END]);
	if (cmd->nxt)
		close(cmd->nxt->fds[READ_END]);
	if (cmd->fds[READ_END] >= 0)
	{
		if ((dup2(cmd->fds[READ_END], STDIN_FILENO)) < 0)
			exit(minishell_perror(1, NULL, NULL));
		close(cmd->fds[READ_END]);
	}
	if (cmd->fds[WRITE_END] >= 0)
	{
		if ((dup2(cmd->fds[WRITE_END], STDIN_FILENO)) < 0)
			exit(minishell_perror(1, NULL, NULL));
		close(cmd->fds[WRITE_END]);
	}
}

int	create_fd(int type, char *path, int quoted, char **env)
{
	int	file;

	if (type == GREAT)
		file = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == DGREAT)
		file = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == LESS)
		file = open(path, O_RDONLY);
	else
		file = heredoc(path, quoted, env);
	if (file < 0 && !g_struct.interrupted)
		minishell_perror(0, path, NULL);
	return (file);
}

int	open_files(t_redir *redirections, int *in, int *out, char **env)
{
	while (redirections)
	{
		if (redirections->type == LESS || redirections->type == DLESS)
		{
			*in = create_fd(redirections->type, redirections->path,
					redirections->quoted, env);
			if (*in < 0)
				return (0);
		}
		else
		{
			*out = create_fd(redirections->type, redirections->path,
					redirections->quoted, env);
			if (*out < 0)
				return (0);
		}
		redirections = redirections->nxt;
	}
	return (1);
}

void	link_fds(int *fds, int file, int io)
{
	if (file >= 0)
	{
		if (fds[io] >= 0)
			close(fds[io]);
		fds[io] = file;
	}
}

void	redirect(t_simpleCmd *cmd)
{
	if (cmd->nxt)
		close(cmd->nxt->fds[READ_END]);
	if (cmd->fds[READ_END] >= 0)
	{
		if ((dup2(cmd->fds[READ_END], STDIN_FILENO)) < 0)
			exit(minishell_perror(1, "minishell", NULL));
		close(cmd->fds[READ_END]);
	}
	if (cmd->fds[WRITE_END] >= 0)
	{
		if ((dup2(cmd->fds[WRITE_END], STDOUT_FILENO)) < 0)
			exit(minishell_perror(1, "minishell", NULL));
		close(cmd->fds[WRITE_END]);
	}
}
