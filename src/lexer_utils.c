/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:21:56 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/26 13:36:40 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*divide_str(char *line, int start, int end)
{
	char *sub_str;

	if (start != end)
	{
		sub_str = ft_substr(line, start, (end - start));
		return (sub_str);
	}
	return (NULL);
}

void	save_buffer(t_lexer *lexer, char *line)
{
	char *sub_str;
	char *tmp;

	sub_str = divide_str(line, lexer->start, lexer->end);
	if (sub_str)
	{
		if (lexer->buffer)
		{
			tmp = lexer->buffer;
			lexer->buffer = ft_strjoin(tmp, sub_str);
			free(tmp);
			free(sub_str);
		}
		else
			lexer->buffer = sub_str;
	}
}
