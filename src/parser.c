/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:33:13 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/22 15:29:22 by fgata-va         ###   ########.fr       */
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
	return (commands);
}

void	init_parser(t_parser *parser, t_cmd **cmd)
{
	parser->argc = 0;
	parser->args = NULL;
	parser->redirs = NULL;
	*cmd = init_cmds();
}

void	free_parser(t_parser *parser)
{
	if (parser->args)
		ft_lstclear(&parser->args, free);
	delete_redirs(parser->redirs);
}

int	analyse_tokens(t_list *tokens, t_parser *parser, t_cmd *commands)
{
	int	status;

	status = 0;
	while (tokens && status == 0)
	{
		parser->type = ((t_token *)tokens->content)->type;
		if (parser->type == WORD)
			add_arg(parser, ((t_token *)tokens->content)->word);
		else if (parser->type == PIPE)
			status = add_cmd(parser, commands);
		else
			status = add_redir(&tokens, &parser->redirs);
		tokens = tokens->next;
	}
	return (status);
}

t_cmd	*parser(t_list *tokens)
{
	t_cmd		*commands;
	t_parser	parser;
	int			status;

	init_parser(&parser, &commands);
	status = analyse_tokens(tokens, &parser, commands);
	if (status == 0 && (parser.args || parser.redirs))
		add_cmd(&parser, commands);
	else
	{
		if (status == 0)
			printf("minishell: syntax error: unexpected end of file\n");
		delete_cmd(&commands);
		free_parser(&parser);
	}
	return (commands);
}
