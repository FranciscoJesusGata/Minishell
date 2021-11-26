/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/26 16:45:15 by fportalo         ###   ########.fr       */
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
	if (!ft_strncmp(cmd->cmds->argv[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd->cmds->argv[0], "env", 3))
		ft_env(env);
	else if (!ft_strncmp(cmd->cmds->argv[0], "echo", 4))
		ft_echo(cmd->cmds->argc, cmd->cmds->argv);
	else if (!ft_strncmp(cmd->cmds->argv[0], "export", 6))
		printf("executing export...\n");
	else if (!ft_strncmp(cmd->cmds->argv[0], "unset", 5))
		printf("executing unset...\n");
	else if (!ft_strncmp(cmd->cmds->argv[0], "cd", 2))
		printf("executing cd...\n");
	else if(!ft_strncmp(cmd->cmds->argv[0], "exit", 4))
		printf("executing exit...\n");
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
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, cmd->cmds->argv[0]);
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
}
