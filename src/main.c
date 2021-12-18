/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/18 15:40:40 by fportalo         ###   ########.fr       */
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

t_cmd	*lexing_parsing(char *line, char **env)
{
	t_list	*tokens;
	t_cmd	*cmd;

	cmd = NULL;
	tokens = lexer(line, env);
	if (tokens)
		cmd = parser(tokens);
	if (cmd)
		create_pipes(cmd->cmds);
	ft_lstclear(&tokens, free);
	return (cmd);
}

int		g_exit_code;

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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	line = launch_term();
	while (line)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		if (*line)
		{
			cmd = lexing_parsing(line, env);
			if (cmd)
			{
				g_exit_code = executor(&env, cmd);
				delete_cmd(&cmd);
			}
		}
		free(line);
		line = launch_term();
	}
	ending_minishell();
	return (g_exit_code);
}
