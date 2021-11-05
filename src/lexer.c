/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/04 17:16:17 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lexer(char *line)
{
	t_lexer	lexer;

	ini_lexer(&lexer);
	while (line[lexer.end])
	{
		if (line[lexer.end] == SPACEX)
			is_space(&lexer, line);
		else if (line[lexer.end] == SQUOTE)
			is_squote(&lexer, line);
		else if (line[lexer.end] == DQUOTE)
			is_dquote(&lexer, line);
		else if (line[lexer.end] == EXPAND)
			is_expand(&lexer, line);
		else if (ft_strchr("<|>", line[lexer.end]))
			is_meta(&lexer, line);
		else
			lexer.end++;
	}
	create_token(&lexer, line, WORD);
	return (lexer.tokens);
}
