/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/24 17:05:14 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_env	env;

	argc = 0;
	argv = NULL;
	init_env(&env, envp);
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
