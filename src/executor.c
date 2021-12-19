/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 18:28:46 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_cmds(t_simpleCmd *s_cmd)
{
	int	exit_code;

	exit_code = 0;
	while (s_cmd)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(s_cmd->pid, &exit_code, 0);
		s_cmd = s_cmd->nxt;
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	return (get_exit_code(exit_code));
}

void	fork_cmds(t_simpleCmd *s_cmd, char **path, char ***env, int builtin)
{
	pid_t	pid;

	while (s_cmd)
	{
		if (s_cmd->nxt)
			create_pipes(s_cmd);
		pid = fork();
		if (!pid)
			exit(exec_cmd(s_cmd, builtin, env, path));
		close(s_cmd->fds[WRITE_END]);
		close(s_cmd->fds[READ_END]);
		s_cmd->pid = pid;
		s_cmd = s_cmd->nxt;
		if (s_cmd)
			builtin = is_builtin(s_cmd->argv[0]);
	}
}

void	no_fork(t_simpleCmd *cmd, char ***env)
{
	int	tmpin;
	int	tmpout;

	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDIN_FILENO);
	redirect(cmd);
	exec_builtin(cmd, env);
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
}

int	executor(char ***env, t_cmd *cmd)
{
	int		exit_code;
	char	**path;
	int		builtin;

	path = get_path(*env);
	exit_code = 0;
	builtin = is_builtin(cmd->cmds->argv[0]);
	if (cmd->count == 1 && builtin)
	{
		if (!redirections(cmd->cmds->redirs, (int *)&cmd->cmds->fds, *env))
			exit_code = 1;
		else
			no_fork(cmd->cmds, env);
	}
	else
	{
		fork_cmds(cmd->cmds, path, env, builtin);
		exit_code = wait_cmds(cmd->cmds);
	}
	if (path)
		ft_freearray(path);
	return (exit_code);
}
