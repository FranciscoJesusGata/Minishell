/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:31:26 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/17 18:39:03 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_simpleCmd *cmd, char ***env)
{
	int	len;

	len = ft_strlen(cmd->argv[0]);
	if (!ft_strncmp(cmd->argv[0], "pwd", len))
		ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "env", len))
		ft_env(*env);
	else if (!ft_strncmp(cmd->argv[0], "echo", len))
		ft_echo(cmd->argc, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "export", len))
		ft_export(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "unset", len))
		ft_unset(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "cd", len))
		ft_cd(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "exit", len))
		ft_exit(cmd->argv, cmd->argc);
}

int	exec_cmd(t_simpleCmd *cmd, int is_builtin, char ***env, char **path)
{
	char	*bin_path;
	int		exit_status;

	bin_path = NULL;
	exit_status = 0;
	if (!redirections(cmd->redirs, (int *)&cmd->fds))
		return (1);
	if (is_builtin)
		exec_builtin(cmd, env);
	else
	{
		bin_path = find_binary(cmd->argv[0], path);
		if (!bin_path && cmd->argv[0])
			exit_status = 127;
		else
		{
			redirect(cmd);
			execve(bin_path, cmd->argv, *env);
		}
	}
	return (exit_status);
}
