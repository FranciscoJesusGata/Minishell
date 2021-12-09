/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 16:01:54 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_simpleCmd *cmds)
{
	int	pipe_fds[2];

	while (cmds->nxt)
	{
		if ((pipe(pipe_fds)) < 0)
			exit(minishell_perror(1, "pipe error", NULL));
		cmds->fds[WRITE_END] = pipe_fds[WRITE_END];
		cmds->nxt->fds[READ_END] = pipe_fds[READ_END];
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
