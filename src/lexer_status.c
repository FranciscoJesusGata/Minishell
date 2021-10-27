/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:43:24 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/27 16:13:42 by fportalo         ###   ########.fr       */
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
