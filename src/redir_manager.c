/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:30:34 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/19 23:02:06 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redi(t_list *tokens)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		malloc_error();
	new->type = ((t_token *)tokens->content)->type;
	new->path = ((t_token *)tokens->next->content)->word;
	new->quoted = ((t_token *)tokens->next->content)->quoted;
	new->nxt = NULL;
	return (new);
}

void	redir_add_back(t_redir **redirs, t_redir *new)
{
	t_redir	*iterable;

	iterable = *redirs;
	while (iterable->nxt)
		iterable = iterable->nxt;
	iterable->nxt = new;
}

void	create_redir(t_list **tokens, t_redir **redirs)
{
	t_redir	*new;

	new = new_redi(*tokens);
	if (!*redirs)
		*redirs = new;
	else
		redir_add_back(redirs, new);
	*tokens = (*tokens)->next;
}

void	add_heredoc(t_list **tokens, t_redir **redirs)
{
	t_redir	*iterable;

	iterable = *redirs;
	while (iterable && iterable->type != DLESS)
		iterable = iterable->nxt;
	if (iterable)
	{
		free(iterable->path);
		iterable->path = ((t_token *)(*tokens)->next->content)->word;
		*tokens = (*tokens)->next;
	}
	else
		create_redir(tokens, redirs);
}

int	add_redir(t_list **tokens, t_redir **redirs)
{
	if ((*tokens)->next && ((t_token *)(*tokens)->next->content)->type == WORD)
	{
		if (((t_token *)(*tokens)->content)->type == DLESS)
			add_heredoc(tokens, redirs);
		else
			create_redir(tokens, redirs);
		return (0);
	}
	if (!(*tokens)->next)
		parse_error('\n');
	else if (((t_token *)(*tokens)->next->content)->type != WORD)
		parse_error(((t_token *)(*tokens)->next->content)->type);
	return (1);
}
