/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:27:38 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/05 13:54:26 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*newtkn(char **word, int type)
{
	t_token	*new;

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

	if (lexer->start != lexer->end && type == WORD)
		save_buffer(lexer, word);
	tkn = newtkn(&lexer->buffer, type);
	if (tkn)
		ft_lstadd_back(&lexer->tokens, tkn);
}

void	delete_token(void *tkn)
{
	if (((t_token *)tkn)->type == WORD)
		free(((t_token *)tkn)->word);
	free(tkn);
}

int	get_metatype(char *line, int start, int end)
{
	if ((end - start) == 1)
		return (line[start]);
	else if (line[start] == '>')
		return (DGREAT);
	else
		return (DLESS);
}
