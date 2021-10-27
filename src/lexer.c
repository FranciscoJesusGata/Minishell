/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/27 16:08:58 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	create_token(t_lexer *lexer, char *line)
{
	char	*sub_str;
	char	*tmp;

	sub_str = divide_str(line, lexer->start, lexer->end);
	if (sub_str || lexer->buffer)
	{
		if (sub_str && lexer->buffer)
		{
			tmp = sub_str;
			sub_str = ft_strjoin(lexer->buffer, tmp);
			free(tmp);
			free(lexer->buffer);
			lexer->buffer = NULL;
		}
		else if (!sub_str)
		{
			sub_str = lexer->buffer;
			lexer->buffer = NULL;
		}
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
		//if (line[lexer.end] == XPAND) // ·$$
		//{

		//}
		lexer.end++;
	}
	create_token(&lexer, line);
	return (lexer.tokens);
}

