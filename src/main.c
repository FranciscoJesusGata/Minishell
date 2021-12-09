/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 12:35:48 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_simpleCmd *cmds)
{
	while (cmds->nxt)
	{
		if ((pipe(cmds->fds)) < 0)
		{
			printf("minishell: pipe error: %s", strerror(errno));
			exit(1);
		}
		cmds->nxt->prev = cmds->fds;
		cmds = cmds->nxt;
	}
}

t_cmd	*lexing_parsing(char *line)
{
	t_list	*tokens;
	t_cmd	*cmd;

	cmd = NULL;
	tokens = lexer(line);
	if (tokens)
	{
		print_tokens(tokens);
		cmd = parser(tokens);
	}
	ft_lstclear(&tokens, free);
	if (cmd)
		print_cmd(cmd);
	return (cmd);
}

int	main(void)
{
	char	*line;
	t_cmd	*cmd;

	welcome();
	line = launch_term();
	while (line)
	{
		if (*line)
		{
			cmd = lexing_parsing(line);
			if (cmd)
				delete_cmd(&cmd);
		}
		free(line);
		line = launch_term();
	}
	clear_history();
	system("leaks minishell");
}
