/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/10 17:39:36 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	is_error(t_simpleCmd *cmd, char **env_path)
{
	if (!ft_strchr(cmd->argv[0], '/') || !env_path)
		printf("minishell: %s: No such file or directory\n", cmd->argv[0]);
	else
		printf("minishell: %s: command not found\n", cmd->argv[0]);
}

int	is_builtin(t_simpleCmd *cmd, t_env *env)
{
	if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen("pwd")))
		ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen("env")))
		ft_env(env);
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

char	*find_binary(t_simpleCmd *cmd, t_env *env)
{
	int		i;
	int		fd;
	char	*path;

	i = 0;
	while (env->path[i])
	{
		path = ft_strdup(env->path[i]);
		path = clean_strjoin(path, "/");
		path = clean_strjoin(path, cmd->argv[0]);
		fd = open(path, O_RDONLY);
		if (fd > 0)
			return (path);
		else
			free(path);
		close(fd);
		i++;
	}
	return (NULL);
}

int	is_binary(t_simpleCmd *cmd, t_env *env, char **path)
{
	*path = find_binary(cmd, env);
	if (*path)
	{
		printf("Path is: %s\n", *path);
		free(*path);
		*path = NULL;
		return (1);
	}
	return (0);
}

int	single_cmd(t_env *env, t_simpleCmd *cmd)
{
	char		*bin_path;
	int			pid;
	int			exit_code;

	if (is_binary(cmd, env, &bin_path))
	{
		pid = fork();
		if (!pid)
		{
			//redirect
			//exec
			exit (0);
		}
		exit_code = waitpid(pid, NULL, 0);
		exit_code = get_exit_code(exit_code);
	}
	else
	{
		//redirect
		if (!is_builtin(cmd, env))
			is_error(cmd, env->path);
		exit_code = 127;
		//recover stdin and stdout
	}
	return (exit_code);
}

void	multiple_cmds(t_env *env, t_simpleCmd *cmd)
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
				if (!is_binary(cmd, env, &bin_path))
				{
					is_error(cmd, env->path);
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

char	**chop_paths(char *raw_path)
{
	char	**paths;

	raw_path += 5;
	paths = ft_split(raw_path, ':');
	return (paths);
}

int	executor(t_env *env, t_cmd *cmd)
{
	t_simpleCmd	*s_cmd;
	int			exit_code;
	
	s_cmd = cmd->cmds;
	exit_code = 0;
	if (cmd->count == 1)
		exit_code = single_cmd(env, cmd->cmds);
	else
	{
		s_cmd = cmd->cmds;
		while (s_cmd)
		{
			exit_code = waitpid(s_cmd->pid, NULL, 0);
			s_cmd = s_cmd->nxt;
		}
		exit_code = get_exit_code(exit_code);
	}
	return (exit_code);
}
