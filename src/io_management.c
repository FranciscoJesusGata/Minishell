/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:41:10 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/09 15:59:47 by fgata-va         ###   ########.fr       */
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

	fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		return (fd);
	line = readline("> ");
	while (!line || ft_strncmp(line, delimiter, ft_strlen(line)))
	{
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		write(1, "> ", 2);
		line = readline("> ");
	}
	free(line);
	close(fd);
	fd = open("/tmp/heredoc", O_RDONLY);
	return (fd);
}

int	open_file(int type, char *path)
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
		exit(minishell_perror(1, path, NULL));
	return (file);
}

void	redirections(t_redir *redirections, int **fds)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	while (redirections)
	{
		if (redirections->type == GREAT || redirections->type == DGREAT)
			in = open_file(redirections->type, redirections->path);
		else
			out = open_file(redirections->type, redirections->path);
		redirections = redirections->nxt;
	}
	if (in >= 0)
	{
		if (*fds[READ_END] >= 0)
			close(*fds[READ_END]);
		*fds[READ_END] = in;
	}
	if (out >= 0)
	{
		if (*fds[WRITE_END] >= 0)
			close(*fds[WRITE_END]);
		*fds[WRITE_END] = out;
	}

}
