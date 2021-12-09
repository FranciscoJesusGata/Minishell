/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 16:06:21 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	is_error(t_cmd *cmd)
{
	printf("minishell: %s: command not found\n", cmd->cmds->argv[0]);
}

int	is_builtin(t_cmd *cmd, t_env *env)
{
	printf("\n");
	if (!ft_strncmp(cmd->cmds->argv[0], "pwd", ft_strlen("pwd")))
		ft_pwd();
	else if (!ft_strncmp(cmd->cmds->argv[0], "env", ft_strlen("env")))
		ft_env(env);
	else if (!ft_strncmp(cmd->cmds->argv[0], "echo", ft_strlen("echo")))
		ft_echo(cmd->cmds->argc, cmd->cmds->argv);
	else if (!ft_strncmp(cmd->cmds->argv[0], "export", ft_strlen("export")))
		ft_export(cmd->cmds->argc, cmd->cmds->argv, env);
	else if (!ft_strncmp(cmd->cmds->argv[0], "unset", ft_strlen("unset")))
		ft_unset(cmd->cmds->argc, cmd->cmds->argv, env);
	else if (!ft_strncmp(cmd->cmds->argv[0], "cd", ft_strlen("cd")))
		ft_cd(cmd->cmds->argc, cmd->cmds->argv, env);
	else if(!ft_strncmp(cmd->cmds->argv[0], "exit", ft_strlen("exit")))
		ft_exit(1);
	else
		return (0);
	return (1);
}

char	*find_binary(t_cmd *cmd, t_env *env)
{
	int i;
	int fd;
	char *path;

	i = 0;
	while (env->path[i])
	{
		path = ft_strdup(env->path[i]);
		path = clean_strjoin(path, "/");
		path = clean_strjoin(path, cmd->cmds->argv[0]);
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

int	is_binary(t_cmd *cmd, t_env *env, int i)
{
	char *path;

	if (!i)
	{
		path = find_binary(cmd, env);
		if (path)
		{
			printf("\nPath is: %s\n",path);
			free(path);
			return (1);
		}
	}
	return (0);
}

void	executor(t_env *env, t_cmd *cmd)
{
	int i;

	i = 0;
	if (is_builtin(cmd, env))
		i = 1;
	else if(is_binary(cmd, env, i))
		i = 1;
	if (i == 0)
		is_error(cmd);
	system("leaks minishell");
}
