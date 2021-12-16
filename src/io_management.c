/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:41:10 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/15 22:23:22 by fgata-va         ###   ########.fr       */
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

int	heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	signal(SIGINT, SIG_DFL);
	fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		return (fd);
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp(line, delimiter, ft_strlen(line)))
			break ;
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY);
	signal(SIGINT, SIG_IGN);
	return (fd);
}

int	create_fd(int type, char *path)
{
	int	file;

	if (type == GREAT)
		file = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == DGREAT)
		file = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == LESS)
		file = open(path, O_RDONLY);
	else
		file = heredoc(path);
	if (file < 0)
		printf("pipex: %s: %s\n", path, strerror(errno));
	return (file);
}

int	open_files(t_redir *redirections, int *in, int *out)
{
	while (redirections)
	{
		if (redirections->type == LESS || redirections->type == DLESS)
		{
			*in = create_fd(redirections->type, redirections->path);
			if (*in < 0)
				return (0);
		}
		else
		{
			*out = create_fd(redirections->type, redirections->path);
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

int	redirections(t_redir *redirections, int *fds)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (!open_files(redirections, &in, &out))
		return (0);
	link_fds(fds, in, READ_END);
	link_fds(fds, out, WRITE_END);
	return (1);
}

void	redirect(t_simpleCmd *cmd)
{
	if (cmd->fds[READ_END] >= 0 && (dup2(cmd->fds[READ_END], STDIN_FILENO)) < 0)
		exit(minishell_perror(1, "minishell", NULL));
	close(cmd->fds[READ_END]);
	if (cmd->fds[WRITE_END] >= 0 && (dup2(cmd->fds[WRITE_END], STDOUT_FILENO)) < 0)
		exit(minishell_perror(1, "minishell" , NULL));
	close(cmd->fds[WRITE_END]);
	if (cmd->prev)
		close(cmd->prev[WRITE_END]);
	if (cmd->nxt)
		close(cmd->nxt->fds[READ_END]);
}