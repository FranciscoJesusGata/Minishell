/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:21:56 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/05 13:53:49 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ini_lexer(t_lexer *lexer)
{
	lexer->start = 0;
	lexer->end = 0;
	lexer->tokens = NULL;
	lexer->buffer = NULL;
}

char	*divide_str(char *line, int start, int end)
{
	char	*sub_str;

	if (start != end)
	{
		sub_str = ft_substr(line, start, (end - start));
		return (sub_str);
	}
	return (NULL);
}

void	save_buffer(t_lexer *lexer, char *line)
{
	char	*sub_str;

	sub_str = divide_str(line, lexer->start, lexer->end);
	concat(&lexer->buffer, sub_str);
}

void	concat(char **dst, char *src)
{
	char	*tmp;

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

void	print_tokens(t_list *tokens)
{
	int	type;

	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		if (type == WORD)
			printf("token [%p]: \"%s\"\n", tokens->content,
				(char *)((t_token *)tokens->content)->word);
		else
		{
			if (type == PIPE)
				printf("token [%p]: PIPE\n", tokens->content);
			else if (type == GREAT)
				printf("token [%p]: GREAT\n", tokens->content);
			else if (type == LESS)
				printf("token [%p]: LESS\n", tokens->content);
			else if (type == DLESS)
				printf("token [%p]: DLESS\n", tokens->content);
			else if (type == DGREAT)
				printf("token [%p]: DGREAT\n", tokens->content);
		}
		tokens = tokens->next;
	}
}
