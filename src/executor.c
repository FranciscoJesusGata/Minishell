/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/11 18:52:02 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_error(t_simpleCmd *cmd, char **env_path)
{
	if (!ft_strchr(cmd->argv[0], '/') || !env_path)
		printf("minishell: %s: No such file or directory\n", cmd->argv[0]);
	else
		printf("minishell: %s: command not found\n", cmd->argv[0]);
}

int	is_builtin(t_simpleCmd *cmd, char ***env)
{
	if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen("pwd")))
		ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen("env")))
		ft_env(*env);
	else if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen("echo")))
		ft_echo(cmd->argc, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "export", ft_strlen("export")))
		ft_export(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "unset", ft_strlen("unset")))
		ft_unset(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "cd", ft_strlen("cd")))
		ft_cd(cmd->argc, cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen("exit")))
		ft_exit(cmd->argv[1]);
	else
		return (0);
	return (1);
}

char	*find_binary(t_simpleCmd *cmd, char **path)
{
	int		i;
	int		found;
	char	*bin_path;

	i = 0;
	while (path[i])
	{
		bin_path = ft_strdup(path[i]);
		bin_path = clean_strjoin(bin_path, "/");
		bin_path = clean_strjoin(bin_path, cmd->argv[0]);
		found = access(bin_path, X_OK);
		if (found == 0)
			return (bin_path);
		free(bin_path);
		i++;
	}
	return (NULL);
}

int	is_binary(t_simpleCmd *cmd, char **path, char **bin_path)
{
	*bin_path = find_binary(cmd, path);
	if (*path)
	{
		printf("Path is: %s\n", *bin_path);
		free(*bin_path);
		*bin_path = NULL;
		return (1);
	}
	return (0);
}

int	single_cmd(char ***env, char **path, t_simpleCmd *cmd)
{
	char		*bin_path;
	int			pid;
	int			exit_code;

	if (is_binary(cmd, path, &bin_path))
	{
		pid = fork();
		if (!pid)
		{
			//redirect
			//exec
			exit (0);
		}
		exit_code = waitpid(pid, NULL, 0);
		//exit_code = get_exit_code(exit_code);
	}
	else
	{
		//redirect
		if (!is_builtin(cmd, env))
			is_error(cmd, path);
		exit_code = 127;
		//recover stdin and stdout
	}
	return (exit_code);
}

void	multiple_cmds(char ***env, char **path, t_simpleCmd *cmd)
{
	char	*bin_path;
	int		pid;

	while (cmd)
	{
		pid = fork();
		if (!pid)
		{
			//redirections
			if (!is_builtin(cmd, env))
			{
				if (!is_binary(cmd, path, &bin_path))
				{
					is_error(cmd, path);
					exit(127);
				}
				//execute
			}
			exit(0);
		}
		cmd->pid = pid;
		cmd = cmd->nxt;
	}
	
}

char	**get_path(char **envp)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i])
		paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

int	executor(char ***env, t_cmd *cmd)
{
	t_simpleCmd	*s_cmd;
	int			exit_code;
	char		**path;
	
	s_cmd = cmd->cmds;
	exit_code = 0;
	path = get_path(*env);
	if (cmd->count == 1)
		exit_code = single_cmd(env, path, cmd->cmds);
	else
	{
		multiple_cmds(env, path, cmd->cmds);
		s_cmd = cmd->cmds;
		while (s_cmd)
		{
			exit_code = waitpid(s_cmd->pid, NULL, 0);
			s_cmd = s_cmd->nxt;
		}
		//exit_code = get_exit_code(exit_code);
	}
	ft_freearray(path);
	return (exit_code);
}
