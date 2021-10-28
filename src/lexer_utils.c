/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:21:56 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/28 13:22:57 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ini_lexer(t_lexer *lexer)
{
	lexer->start = 0;
	lexer->end = 0;
	lexer->tokens = NULL;
	lexer->buffer = NULL;
}

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
