/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/10 12:08:00 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	if (lexer->buffer)
		free(lexer->buffer);
	ft_lstclear(&lexer->tokens, delete_token);
}

t_list	*lexer(char *line, t_env *env)
{
	t_lexer	lexer;
	int		status;

	ini_lexer(&lexer);
	status = 0;
	while (line[lexer.end] && status == 0)
	{
		if (line[lexer.end] == SPACEX)
			is_space(&lexer, line);
		else if (line[lexer.end] == SQUOTE)
			status = is_squote(&lexer, line);
		else if (line[lexer.end] == DQUOTE)
			status = is_dquote(&lexer, line, env);
		else if (line[lexer.end] == EXPAND && lexer.expand)
			is_expand(&lexer, line, env);
		else if (ft_strchr("<|>", line[lexer.end]))
			is_meta(&lexer, line);
		else
			lexer.end++;
	}
	if (status)
		free_lexer(&lexer);
	else
		create_token(&lexer, line, WORD);
	return (lexer.tokens);
}
