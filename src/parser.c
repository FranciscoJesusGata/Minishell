/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:33:13 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/18 12:00:08 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmds(void)
{
	t_cmd	*commands;

	commands = (t_cmd *)malloc(sizeof(t_cmd));
	if (!commands)
		malloc_error();
	commands->count = 0;
	commands->cmds = NULL;
	commands->redirs = NULL;
	return (commands);
}

t_cmd		*parser(t_list *tokens)
{
	t_cmd	*commands;
	t_list	*args;
	int		argc;
	int		type;

	commands = init_cmds();
	argc = 0;
	args = NULL;
	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		if (type == WORD)
		{
			add_arg(&args, ((t_token *)tokens->content)->word);
			argc++;
		}
		else
		{
			if (type == PIPE)
			{
				//if (argc)
					//error bash: syntax error near unexpected token `|'
				add_cmd(&args, argc, &commands->cmds, &commands->count);
				argc = 0;
			}
			else if (add_redir(tokens, &commands->redirs) == 0) 
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	if (argc)
		add_cmd(&args, argc, &commands->cmds, &commands->count);
	return (commands);
}
