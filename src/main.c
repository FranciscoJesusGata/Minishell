/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 21:00:15 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lexing_parsing(char *line, char **env)
{
	t_list	*tokens;
	t_cmd	*cmd;

	cmd = NULL;
	tokens = lexer(line, env);
	if (tokens)
		cmd = parser(tokens);
	if (cmd)
		ft_lstclear(&tokens, free);
	return (cmd);
}

void	ending_minishell(void)
{
	printf("\x1b[1F");
	printf("\001\e[38;5;38m\002MiniShell ~ 👉  \001\033[39mexit\n");
	clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	char	**env;

	argc = 0;
	argv = NULL;
	g_exit_code = 0;
	env = init_env(envp);
	welcome();
	line = launch_term();
	while (line)
	{
		if (*line)
		{
			cmd = lexing_parsing(line, env);
			if (cmd)
			{
				g_exit_code = executor(&env, cmd);
				g_interrupted = 0;
				delete_cmd(&cmd);
			}
		}
		free(line);
		line = launch_term();
	}
	ending_minishell();
	return (g_exit_code);
}
