/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:28:18 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/17 18:41:42 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int	len;

	if (cmd)
	{
		len = ft_strlen(cmd);
		if (len > 0 && (!ft_strncmp(cmd, "pwd", len)
				|| !ft_strncmp(cmd, "env", len)
				|| !ft_strncmp(cmd, "echo", len)
				|| !ft_strncmp(cmd, "export", len)
				|| !ft_strncmp(cmd, "unset", len)
				|| !ft_strncmp(cmd, "cd", len)
				|| !ft_strncmp(cmd, "exit", len)))
			return (1);
	}
	return (0);
}

char	*search_in_path(char *arg, char **path)
{
	int		i;
	int		found;
	char	*bin_path;

	found = -1;
	bin_path = NULL;
	i = 0;
	if (ft_strlen(arg))
	{
		while (path[i])
		{
			bin_path = ft_strdup(path[i]);
			bin_path = clean_strjoin(bin_path, "/");
			bin_path = clean_strjoin(bin_path, arg);
			found = access(bin_path, X_OK);
			if (!found)
				break ;
			free(bin_path);
			bin_path = NULL;
			i++;
		}
	}
	return (bin_path);
}

char	*find_binary(char *arg, char **path)
{
	int		found;
	char	*bin_path;

	found = -1;
	bin_path = NULL;
	if (arg)
	{
		if (!path || ft_strchr(arg, '/'))
		{
			found = access(arg, X_OK);
			if (found < 0)
				printf("minishell: %s: No such file or directory\n", arg);
			else
				bin_path = arg;
		}
		else
		{
			bin_path = search_in_path(arg, path);
			if (!bin_path)
				printf("minishell: %s: command not found\n", arg);
		}
	}
	return (bin_path);
}

int	get_exit_code(int exit_code)
{
	if (WIFSIGNALED(exit_code))
		return (128 + WTERMSIG(exit_code));
	else if (WIFSTOPPED(exit_code))
		return (WSTOPSIG(exit_code));
	else if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	else
		return (exit_code);
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
