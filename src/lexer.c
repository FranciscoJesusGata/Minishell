/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/26 12:55:26 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	create_token(t_lexer *lexer, char *line)
{
	char	*sub_str;

	if (lexer->start != lexer->end)
	{
		sub_str = ft_substr(line, lexer->start, lexer->end - lexer->start);
		if (sub_str)
			ft_lstadd_back(&lexer->tokens, ft_lstnew(sub_str));
	}
}

t_list	*lexer(char *line)
{
	t_lexer lexer;

	lexer.start = 0;
	lexer.end = 0;
	lexer.tokens = NULL;
	lexer.buffer = NULL;
	while (line[lexer.end])
	{
		if (line[lexer.end] == 32)
		{
			is_space(&lexer, line);
			continue ;
		}
		//if (line[lexer.end] == SQUOTE) // '
		//	is_squote(&lexer, line);
		//if (line[lexer.end] == DQUOTE) // ""
		//{

		//}
		//if (line[lexer.end] == XPAND) // ·$$
		//{

		//}
		lexer.end++;
	}
	create_token(&lexer, line);
	return (lexer.tokens);
}

