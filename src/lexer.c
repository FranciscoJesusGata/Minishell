/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/28 13:22:46 by fportalo         ###   ########.fr       */
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
	t_lexer lexer;

	ini_lexer(&lexer);
	while (line[lexer.end])
	{
		if (line[lexer.end] == SPACEX)
		{
			is_space(&lexer, line);
			continue ;
		}
		if (line[lexer.end] == SQUOTE)
		{
			is_squote(&lexer, line);
			continue ;
		}
		if (line[lexer.end] == DQUOTE)
		{
			is_dquote(&lexer, line);
			continue ;
		}
		if (line[lexer.end] == EXPAND)
		{
			is_expand(&lexer, line);
			continue ;
		}
		lexer.end++;
	}
	create_token(&lexer, line);
	return (lexer.tokens);
}

