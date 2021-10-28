/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:43:24 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/28 13:42:09 by fportalo         ###   ########.fr       */
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
	while(line[lexer->end] != SQUOTE)
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
	while(line[lexer->end] != DQUOTE)
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

void	is_expand(t_lexer *lexer, char *line)
{
	char *expanded;
	char *tmp;

	lexer->start = lexer->end;
	lexer->end++;
	if (line[lexer->end] == SQUOTE || line[lexer->end] == DQUOTE)
		return ;
	if (line[lexer->end] == SPACEX || line[lexer->end] == '\0')
	{
		save_buffer(lexer, line);
		return ;
	}
	lexer->start = lexer->end;
	while (line[lexer->end] != SPACEX || line[lexer->end] != SQUOTE
			|| line[lexer->end] != DQUOTE)
		lexer->end;

	tmp = lexer->buffer;
	lexer->buffer = ft_strjoin(tmp, sub_str);
	free(tmp);
	free(sub_str);

	expanded = getenv(expanded);
	//concat(lexer->buffer, expanded);
	return ;
}
