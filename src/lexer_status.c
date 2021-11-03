/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:43:24 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/03 12:54:37 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	is_space(t_lexer *lexer, char *line)
{
	create_token(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
}

void	is_squote(t_lexer *lexer, char *line)
{
	if (lexer->start != lexer->end)
		save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
	while (line[lexer->end] != SQUOTE)
	{
		if (!line[lexer->end])
		{
			perror("wa wa");
			exit(1);
		}
		lexer->end++;
	}
	save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
}

void	is_dquote(t_lexer *lexer, char *line)
{
	if (lexer->start != lexer->end)
		save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
	while (line[lexer->end] != DQUOTE)
	{
		if (!line[lexer->end])
		{
			perror("wa wa");
			exit(1);
		}
		if (line[lexer->end] == '$')
			is_expand(lexer, line);
		else
			lexer->end++;
	}
	save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
}

void	is_expand(t_lexer *lexer, char *line)
{
	char	*expanded;
	char	*tmp;

	lexer->start = lexer->end;
	lexer->end++;
	if (line[lexer->end] == SPACEX || line[lexer->end] == '\0')
		return ;
	lexer->start = lexer->end;
	while (!ft_strchr("\"' ", line[lexer->end]) && line[lexer->end])
		lexer->end++;
	tmp = divide_str(line, lexer->start, lexer->end);
	expanded = getenv(tmp);
	free(tmp);
	if (expanded)
		concat(&lexer->buffer, ft_strdup(expanded));
	else
		concat(&lexer->buffer, ft_strdup(""));
	lexer->start = lexer->end;
}

void	is_meta(t_lexer *lexer, char *line)
{
	if (lexer->start != lexer->end || lexer->buffer)
	{
		create_token(lexer, line);
		lexer->start = lexer->end;
	}
	if (line[lexer->end] == line[lexer->end + 1] && ft_strchr("<>", line[lexer->end]))
		lexer->end++;
	lexer->end++;
	create_token(lexer, line);
	lexer->start = lexer->end;
}
