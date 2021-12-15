/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:01:05 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/09 12:46:52 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list2matrix(int count, t_list **lst)
{
	int		i;
	char	**argv;
	t_list	*nxt;

	argv = malloc(sizeof(char *) * count + 1);
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		nxt = (*lst)->next;
		argv[i] = (*lst)->content;
		free(*lst);
		*lst = nxt;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

t_simpleCmd	*new_cmd(int *argc, char **argv, t_redir **redirs)
{
	t_simpleCmd	*new_cmd;

	new_cmd = (t_simpleCmd *)malloc(sizeof(t_simpleCmd));
	if (!new_cmd)
		malloc_error();
	new_cmd->argc = *argc;
	new_cmd->argv = argv;
	new_cmd->redirs = *redirs;
	new_cmd->nxt = NULL;
	*redirs = NULL;
	*argc = 0;
	new_cmd->fds[0] = -1;
	new_cmd->fds[1] = -1;
	return (new_cmd);
}

int	add_cmd(t_parser *parser, t_cmd *cmd)
{
	t_simpleCmd	*new;
	t_simpleCmd	*iter;
	char		**argv;

	if (parser->args || parser->redirs)
	{
		argv = list2matrix(parser->argc, &parser->args);
		if (!argv)
			malloc_error();
		new = new_cmd(&parser->argc, argv, &parser->redirs);
		if (!cmd->cmds)
			cmd->cmds = new;
		else
		{
			iter = cmd->cmds;
			while (iter->nxt)
				iter = iter->nxt;
			iter->nxt = new;
		}
		cmd->count++;
		return (0);
	}
	parse_error('|');
	return (1);
}

void	delete_cmd(t_cmd **cmd)
{
	t_simpleCmd	*scmd;
	t_simpleCmd	*s_nxt;
	t_redir		*redir;
	int			i;

	scmd = (*cmd)->cmds;
	while (scmd)
	{
		redir = scmd->redirs;
		s_nxt = scmd->nxt;
		i = 0;
		if (scmd->fds[0] >= 0)
			close(scmd->fds[0]);
		if (scmd->fds[1] >= 0)
			close(scmd->fds[1]);
		delete_matrix(scmd->argv, scmd->argc);
		delete_redirs(redir);
		free(scmd);
		scmd = s_nxt;
	}
	free(*cmd);
	*cmd = NULL;
}

void	parse_error(int token)
{
	printf("minishell: syntax error near unexpected token ");
	if (token == GREAT || token == LESS || token == PIPE)
		printf("`%c'\n", token);
	else if (token == '\n')
		printf("`newline'\n");
	else if (token == DGREAT)
		printf("`>>'\n");
	else
		printf("`<<'\n");
}
