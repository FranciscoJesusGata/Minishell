/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:41:10 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/19 20:38:17 by fgata-va         ###   ########.fr       */
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

char *do_expand(int start, int end, char *line, char **env)
{
	char	*tmp;
	char	*expanded;

	tmp = divide_str(line, start, end);
	expanded = ft_getenv(tmp, env);
	free(tmp);
	return (expanded);
}

char	*heredoc_expand(char *line, char **env)
{
	char	*nxt_dollar;
	char	*new_line;
	int		start;
	int		end;

	nxt_dollar = ft_strchr(line, '$');
	while (nxt_dollar)
	{
		start = nxt_dollar - line;
		nxt_dollar++;
		start++;
		end = start;
		while (line[end] && (ft_isalnum(line[end]) || line[end] == '_'))
			end++;
		new_line = ft_substr(line, 0, start - 1);
		concat(&new_line, do_expand(start, end, line, env));
		concat(&new_line, ft_substr(line, end, ft_strlen(line)));
		free(line);
		line = new_line;
		nxt_dollar = ft_strchr(line, '$');
	}
	return (new_line);
}

int	heredoc(char *delimiter, int quoted, char **env)
{
	char	*line;
	int		fd;
	size_t	len;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc);
	fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		return (fd);
	len = ft_strlen(delimiter);
	line = readline("> ");
	while (line && !g_interrupted)
	{
		if (!ft_strncmp(line, delimiter, len) && len == ft_strlen(line))
			break ;
		if (!quoted && ft_strchr(line, '$'))
			line = heredoc_expand(line, env);
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd);
	if (g_interrupted)
	{
		unlink("/tmp/heredoc");
		return (-1);
	}
	fd = open("/tmp/heredoc", O_RDONLY);
	signal(SIGQUIT, SIG_DFL);
	return (fd);
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
	if (file < 0 && !g_interrupted)
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
			exit(minishell_perror(1, "minishell" , NULL));
		close(cmd->fds[WRITE_END]);
	}
}

void	create_pipes(t_simpleCmd *cmds)
{
	int	pipe_fds[2];

	if ((pipe(pipe_fds)) < 0)
		exit(minishell_perror(1, "pipe error", NULL));
	cmds->fds[WRITE_END] = pipe_fds[WRITE_END];
	cmds->nxt->fds[READ_END] = pipe_fds[READ_END];
	cmds->nxt->prev = cmds->fds;
}