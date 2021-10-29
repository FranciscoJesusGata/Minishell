/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/29 13:04:19 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	create_token(t_lexer *lexer, char *line)
{
	if (lexer->start != lexer->end || lexer->buffer)
	{
		save_buffer(lexer, line);
		ft_lstadd_back(&lexer->tokens, ft_lstnew(lexer->buffer));
		lexer->buffer = NULL;
	}
}

t_list	*lexer(char *line)
{
	t_lexer	lexer;

	ini_lexer(&lexer);
	while (line[lexer.end])
	{
		if (line[lexer.end] == SPACEX)
			is_space(&lexer, line);
		else if (line[lexer.end] == SQUOTE)
			is_squote(&lexer, line);
		else if (line[lexer.end] == DQUOTE)
			is_dquote(&lexer, line);
		else if (line[lexer.end] == EXPAND)
			is_expand(&lexer, line);
		else if (ft_strchr("<|>", line[lexer.end]))
			is_meta(&lexer, line);
		else
			lexer.end++;
	}
	create_token(&lexer, line);
	return (lexer.tokens);
}
