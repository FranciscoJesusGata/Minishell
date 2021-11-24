/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:23:39 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/22 15:33:04 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(t_parser *parser, char *word)
{
	t_list	*new;

	new = ft_lstnew(word);
	if (!new)
		malloc_error();
	ft_lstadd_back(&parser->args, new);
	parser->argc++;
}

t_redir	*new_redi(t_list *tokens)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		malloc_error();
	new->type = ((t_token *)tokens->content)->type;
	new->path = ((t_token *)tokens->next->content)->word;
	new->nxt = NULL;
	return (new);
}

int	add_redir(t_list **tokens, t_redir **redirs)
{
	t_redir	*new;
	t_redir	*iterable;

	if ((*tokens)->next && ((t_token *)(*tokens)->next->content)->type == WORD)
	{
		new = new_redi(*tokens);
		if (!*redirs)
			*redirs = new;
		else
		{
			iterable = *redirs;
			while (iterable->nxt)
				iterable = iterable->nxt;
			iterable->nxt = new;
		}
		*tokens = (*tokens)->next;
		return (0);
	}
	if (!(*tokens)->next)
		parse_error('\n');
	else if (((t_token *)(*tokens)->next->content)->type != WORD)
		parse_error(((t_token *)(*tokens)->next->content)->type);
	return (1);
}

void	delete_redirs(t_redir *redirs)
{
	t_redir	*nxt;

	while (redirs)
	{
		nxt = redirs->nxt;
		free(redirs->path);
		free(redirs);
		redirs = nxt;
	}
}
