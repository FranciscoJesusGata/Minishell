/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/26 13:42:20 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	create_token(t_lexer *lexer, char *line)
{
	char	*sub_str;

	sub_str = divide_str(line, lexer->start, lexer->end);
	if (sub_str)
		ft_lstadd_back(&lexer->tokens, ft_lstnew(sub_str));
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
		if (line[lexer.end] == SPACEX)
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

