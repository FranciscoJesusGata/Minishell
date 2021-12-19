/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 23:56:56 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_and_execute(char *line, char **env)
{
	t_list	*tokens;
	t_cmd	*cmd;

	cmd = NULL;
	tokens = lexer(line, env);
	if (tokens)
		cmd = parser(tokens);
	if (cmd)
	{
		ft_lstclear(&tokens, free);
		g_struct.exit_code = executor(&env, cmd);
		g_struct.interrupted = 0;
		delete_cmd(&cmd);
	}
}

void	ending_minishell(struct termios *attr)
{
	tcsetattr(STDIN_FILENO, TCSANOW, attr);
	printf("\x1b[1F");
	printf("\001\e[38;5;38m\002MiniShell ~ 👉  \001\033[39mexit\n");
	clear_history();
}

void	init_minishell(char ***env, char **envp, struct termios *attr)
{
	struct termios	*new_attr;

	*env = init_env(envp);
	welcome();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	new_attr = attr;
	tcgetattr(STDIN_FILENO, new_attr);
	attr->c_lflag = ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, new_attr);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			**env;
	struct termios	attr;

	argc = 0;
	argv = NULL;
	init_minishell(&env, envp, &attr);
	line = launch_term();
	while (line)
	{
		if (*line)
			parse_and_execute(line, env);
		free(line);
		line = launch_term();
	}
	ending_minishell(&attr);
	return (g_struct.exit_code);
}
