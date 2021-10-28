/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:21:56 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/28 16:43:13 by fgata-va         ###   ########.fr       */
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

	sub_str = divide_str(line, lexer->start, lexer->end);
	concat(&lexer->buffer, sub_str);
}

void	concat(char **dst, char *src)
{
	char *tmp;

	if (src)
	{
		if (*dst)
		{
			tmp = *dst;
			*dst = ft_strjoin(tmp, src);
			free(tmp);
			free(src);
		}
		else
			*dst = src;
	}
}
