/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:43:24 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/18 15:05:35 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	is_space(t_lexer *lexer, char *line)
{
	create_token(lexer, line, WORD);
	lexer->end++;
	lexer->start = lexer->end;
}

int	is_squote(t_lexer *lexer, char *line)
{
	if (!lexer->quoted)
		lexer->quoted = 1;
	if (lexer->start != lexer->end)
		save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
	while (line[lexer->end] != SQUOTE)
	{
		if (!line[lexer->end])
		{
			printf("minishell: unexpected EOF while looking for matching `''\n\
minishell: syntax error: unexpected end of file\n");
			return (1);
		}
		lexer->end++;
	}
	save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
	return (0);
}

int	is_dquote(t_lexer *lexer, char *line, char **env)
{
	if (!lexer->quoted)
		lexer->quoted = 1;
	if (lexer->start != lexer->end)
		save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
	while (line[lexer->end] != DQUOTE)
	{
		if (!line[lexer->end])
		{
			printf("minishell: unexpected EOF while looking for matching `\"'\n\
minishell: syntax error: unexpected end of file\n");
			return (1);
		}
		if (line[lexer->end] == '$')
			is_expand(lexer, line, env);
		else
			lexer->end++;
	}
	save_buffer(lexer, line);
	lexer->end++;
	lexer->start = lexer->end;
	return (0);
}

void	is_expand(t_lexer *lexer, char *line, char **env)
{
	if (lexer->start != lexer->end)
		save_buffer(lexer, line);
	lexer->start = lexer->end;
	lexer->end++;
	if (line[lexer->end] == '?')
	{
		expand_exclamation(lexer);
		return ;
	}
	if (line[lexer->end] == SPACEX || line[lexer->end] == '\0')
		return ;
	lexer->start = lexer->end;
	while ((ft_isalnum(line[lexer->end]) || line[lexer->end] == '_')
		&& line[lexer->end])
		lexer->end++;
	expand(lexer, line, env);
}

void	is_meta(t_lexer *lexer, char *line)
{
	int		type;

	if (lexer->start != lexer->end || lexer->buffer)
	{
		create_token(lexer, line, WORD);
		lexer->start = lexer->end;
	}
	if (line[lexer->end] == line[lexer->end + 1]
		&& ft_strchr("<>", line[lexer->end]))
		lexer->end++;
	lexer->end++;
	type = get_metatype(line, lexer->start, lexer->end);
	if (type == DLESS)
		lexer->expand = 0;
	create_token(lexer, line, type);
	lexer->start = lexer->end;
}
