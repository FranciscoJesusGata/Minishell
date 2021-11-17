/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:01:05 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/17 19:16:59 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_simpleCmd	*new_cmd(int argc, char **argv)
{
	t_simpleCmd *new_cmd;

	new_cmd = (t_simpleCmd *)malloc(sizeof(t_simpleCmd));
	if (!new_cmd)
		malloc_error();
	new_cmd->argc = argc;
	new_cmd->argv = argv;
	new_cmd->nxt = NULL;
	return (new_cmd);
}

char	**list2matrix(int count, t_list **lst)
{
	int i;
	char **argv;
	t_list *nxt;

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

void	add_cmd(t_list **args, int argc, t_simpleCmd **cmds)
{
	t_simpleCmd *new;
	t_simpleCmd *iter;
	char **argv;

	argv = list2matrix(argc, args);
	if (!argv)
		malloc_error();
	new = new_cmd(argc, argv);
	if (!*cmds)
		*cmds = new;
	else
	{
	iter = *cmds;
	while (iter->nxt)
		iter = iter->nxt;
	iter->nxt = new;
	}
}

void	add_arg(t_list **args, char *word)
{
	t_list *new;

	new = ft_lstnew(word);
	if (!new)
		malloc_error();
	ft_lstadd_back(args, new);
}

int		add_redir(t_list *tokens, t_redir **redirs)
{
	t_redir	*new_redi;
	t_redir	*iterable;

	if (tokens->next && ((t_token *)tokens->next->content)->type == WORD)
	{
		new_redi = (t_redir *)malloc(sizeof(t_redir));
		if (!new_redi)
			malloc_error();
		new_redi->type = ((t_token *)tokens->content)->type;
		new_redi->path = ((t_token *)tokens->next->content)->word;
		new_redi->nxt = NULL;
		if (!*redirs)
			*redirs = new_redi;
		else
		{
			iterable = *redirs;
			while (iterable->nxt)
				iterable = iterable->nxt;
			iterable->nxt = new_redi;
		}
		return (0);
	}
	return (1);
}

void	delete_cmd(t_cmd **cmd)
{
	t_simpleCmd *scmd;
	t_simpleCmd *s_nxt;
	t_redir *redir;
	t_redir *r_nxt;

	scmd = (*cmd)->cmds;
	while (scmd)
	{
		s_nxt = scmd->nxt;
		free(scmd->argv);
		free(scmd);
		scmd = s_nxt;
	}
	redir = (*cmd)->redirs;
	while (redir)
	{
		r_nxt = redir->nxt;
		free(redir);
		redir = r_nxt;
	}
	free(*cmd);
	*cmd = NULL;
}

void	print_argv(t_simpleCmd *cmd, int n_cmd)
{
	int	i;

	i = 0;
	printf("			cmd%d: [", n_cmd);
	while (cmd->argv[i])
	{
		printf("\"%s\"", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(", ");
		i++;
	}
	printf("]\n");
}

void	print_cmd(t_cmd *cmd)
{
	int i;
	t_simpleCmd *iter;
	t_redir		*r_iter;

	printf("cmd	{\n");
	printf("	count = %d\n", cmd->count);
	printf("	cmds:\n");
	printf("		argc: %d\n", cmd->cmds->argc);
	printf("		argv:\n");
	i = 0;
	iter = cmd->cmds;
	while (iter)
	{
		print_argv(iter, i);
		iter = iter->nxt;
		i++;
	}
	r_iter = cmd->redirs;
	printf("		redirections:\n");
	while (r_iter)
	{
		if (r_iter->type < 77)
			printf("			%c ", r_iter->type);
		else if (r_iter->type < DGREAT)
			printf(">>");
		else
			printf("<<");
		printf("\"%s\"\n", r_iter->path);
		r_iter = r_iter->nxt;
	}
	printf("	}\n");
}
