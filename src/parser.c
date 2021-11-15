/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:33:13 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/15 17:59:35 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmds(void)
{
	t_cmd	*commands;

	commands = (t_cmd *)malloc(sizeof(t_cmd));
	if (!commands)
	{
		perror("Error: allocation error");
		exit(1);
	}
	commands->count = 0;
	commands->cmds = NULL;
	commands->redirs = NULL;
	return (commands);
}

void		add_cmd(t_list *tokens, int argc, t_simpleCmd **cmds)
{
	int i;
	char **argv;

	argv = malloc(sizeof(char *) * argc + 1);
	if (!argv)
	{
		perror("Error: allocation error");
		exit(1);
	}
	i = 0;
	while (i < argc)
	{
		argv[i] = ((t_token *)tokens->content)->word;
		tokens = tokens->next;
		i++;
	}
	argv[i] = NULL;
	new_cmd(argc, argv, cmds);
}

int		add_redir(t_list *tokens, t_redir **redirs)
{
	t_redir	*new_redi;
	t_redir	*iterable;

	if (tokens->next && ((t_token *)tokens->next->content)->type == WORD)
	{
		new_redi = (t_redir *)malloc(sizeof(t_redir));
		if (!new_redi)
		{
			perror("Error: allocation error");
			exit(1);
		}
		new_redi->type = ((t_token *)tokens->content)->type;
		new_redi->path = ((t_token *)tokens->next)->word;
		new_redi->nxt = NULL;
		if (!*redirs)
			*redirs = new_redi;
		iterable = *redirs;
		while (iterable->nxt)
			iterable = iterable->nxt;
		iterable->nxt = new_redi;
		return (0);
	}
	return (1);
}

t_cmd		*parser(t_list *tokens)
{
	t_cmd	*commands;
	int		argc;
	int		type;

	commands = init_cmds();
	argc = 0;
	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		if (type == WORD)
			argc++;
		else
		{
			if (argc)
				add_cmd(tokens, argc, &commands->cmds);
			if (add_redir(tokens, &commands->redirs) == 0)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (commands);
}
