/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/13 16:18:16 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", len) || !ft_strncmp(cmd, "env", len) ||
		!ft_strncmp(cmd, "echo", len) || !ft_strncmp(cmd, "export", len) ||
		!ft_strncmp(cmd, "unset", len) || !ft_strncmp(cmd, "cd", len) ||
		!ft_strncmp(cmd, "exit", len))
		return (1);
	return (0);
}

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
		ft_exit(cmd->argv[1]);
}

char	*find_binary(t_simpleCmd *cmd, char **path)
{
	int		i;
	int		found;
	char	*bin_path;

	i = 0;
	found = -1;
	bin_path = NULL;
	if (!path || ft_strchr(cmd->argv[0], '/'))
	{
		found = access(cmd->argv[0], X_OK);
		if (found < 0)
			printf("minishell: %s: No such file or directory\n", cmd->argv[0]);
		else
			bin_path = cmd->argv[0];
	}
	else
	{
		while (path[i] && found < 0)
		{
			if (bin_path)
			{
				free(bin_path);
				bin_path = NULL;
			}
			bin_path = ft_strdup(path[i]);
			bin_path = clean_strjoin(bin_path, "/");
			bin_path = clean_strjoin(bin_path, cmd->argv[0]);
			found = access(bin_path, X_OK);
			i++;
		}
	}
	return (bin_path);
}

int	is_binary(t_simpleCmd *cmd, char **path, char **bin_path)
{
	*bin_path = find_binary(cmd, path);
	printf("%s\n", *bin_path);
	if (*bin_path)
	{
		printf("Path is: %s\n", *bin_path);
		return (1);
	}
	printf("minishell: %s: command not found\n", cmd->argv[0]);
	return (0);
}

int		exec_cmd(t_simpleCmd *cmd, int is_builtin, char ***env, char **path)
{
	char	*bin_path;
	int		exit_status;

	bin_path = NULL;
	exit_status = 0;
	//redirections
	if (is_builtin)
		exec_builtin(cmd, env);
	else if (is_binary(cmd, path, &bin_path))
		execve(bin_path, cmd->argv, *env);
	else
		exit_status = 127;
	return (exit_status);
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
	{
		paths = ft_split(envp[i] + 5, ':');
		if (!paths)
			malloc_error();
	}
	return (paths);
}

int	executor(char ***env, t_cmd *cmd)
{
	t_simpleCmd	*s_cmd;
	int			exit_code;
	char		**path;
	int			builtin;
	pid_t		pid;
	
	s_cmd = cmd->cmds;
	path = get_path(*env);
	exit_code = 0;
	builtin = is_builtin(s_cmd->argv[0]);
	if (cmd->count == 1 && builtin)
		exec_builtin(s_cmd, env);
	else
	{
		s_cmd = cmd->cmds;
		while (s_cmd)
		{
			pid = fork();
			if (!pid)
			{
				exit_code = exec_cmd(s_cmd, builtin, env, path);
				exit (exit_code);
			}
			s_cmd->pid = pid;
			s_cmd = s_cmd->nxt;
			if (s_cmd)
				builtin = is_builtin(s_cmd->argv[0]);
		}
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
