/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:31:26 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/18 17:12:29 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_simpleCmd *cmd, char ***env)
{
	int	el_pibe;

	el_pibe = 0;
	if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen("pwd")))
		el_pibe = ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen("env")))
		el_pibe = ft_env(*env, cmd->argv, cmd->argc);
	else if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen("echo")))
		el_pibe = ft_echo(cmd->argc, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "export", ft_strlen("export")))
		el_pibe = ft_export(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "unset", ft_strlen("unset")))
		el_pibe = ft_unset(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "cd", ft_strlen("cd")))
		el_pibe = ft_cd(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen("exit")))
		el_pibe = ft_exit(cmd->argv, cmd->argc);
	return (el_pibe);
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
	{
		redirect(cmd);
		exit_status = exec_builtin(cmd, env);
	}
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
