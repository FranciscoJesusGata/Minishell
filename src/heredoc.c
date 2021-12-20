/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:46:57 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/20 00:20:13 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_expand(int start, int end, char *line, char **env)
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

void	write_heredoc(int fd, char *delimiter, int quoted, char **env)
{
	size_t	len;
	char	*line;

	len = ft_strlen(delimiter);
	line = readline("> ");
	while (line && !g_struct.interrupted)
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
}

int	heredoc(char *delimiter, int quoted, char **env)
{
	int		fd;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc);
	fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		return (fd);
	write_heredoc(fd, delimiter, quoted, env);
	if (g_struct.interrupted)
	{
		unlink("/tmp/heredoc");
		return (-1);
	}
	fd = open("/tmp/heredoc", O_RDONLY);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	return (fd);
}
