/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:27:38 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/04 16:21:21 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*newtkn(char **word, int type)
{
	t_token *new;

	if (type == WORD && !(*word))
		return (NULL);
	new = (t_token *)malloc(sizeof(t_token));
	if (new)
	{
		if (type == WORD)
		{
			new->word = *word;
			*word = NULL;
		}
		new->type = type;
	}
	return (ft_lstnew(new));
}

void	create_token(t_lexer *lexer, char *word, int type)
{
	t_list	*tkn;

	if (lexer->start != lexer->end)
		save_buffer(lexer, word);
	tkn = newtkn(&lexer->buffer, type);
	if (tkn)
		ft_lstadd_back(&lexer->tokens, tkn);
}

void	delete_token(void *tkn)
{
	free(((t_token *)tkn)->word);
	free(tkn);
}
