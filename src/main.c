/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/20 12:08:34 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_and_execute(char *line, char ***env)
{
	t_list	*tokens;
	t_cmd	*cmd;

	cmd = NULL;
	tokens = lexer(line, *env);
	if (tokens)
		cmd = parser(tokens);
	if (cmd)
	{
		ft_lstclear(&tokens, free);
		g_struct.exit_code = executor(env, cmd);
		g_struct.interrupted = 0;
		delete_cmd(&cmd);
	}
}

void	ending_minishell(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_struct.term_attr);
	ft_putstr_fd("exit\n", 1);
	clear_history();
}

void	init_minishell(char ***env, char **envp)
{
	*env = init_env(envp);
	welcome();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	tcgetattr(STDIN_FILENO, &g_struct.term_attr);
	deactivate_echo_ctl();
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			**env;

	argc = 0;
	argv = NULL;
	init_minishell(&env, envp);
	line = launch_term();
	while (line)
	{
		if (*line)
			parse_and_execute(line, &env);
		free(line);
		line = launch_term();
	}
	ending_minishell();
	return (g_struct.exit_code);
}
