/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/18 12:50:46 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (len > 0 && \
		((!ft_strncmp(str_tolower(cmd), "pwd", len) && len == (int)ft_strlen("pwd")) || \
		(!ft_strncmp(str_tolower(cmd), "env", len) && len == (int)ft_strlen("env")) || \
		(!ft_strncmp(str_tolower(cmd), "echo", len) && len == (int)ft_strlen("echo")) || \
		(!ft_strncmp(str_tolower(cmd), "export", len) && len == (int)ft_strlen("export")) || \
		(!ft_strncmp(str_tolower(cmd), "unset", len) && len == (int)ft_strlen("unset")) || \
		(!ft_strncmp(str_tolower(cmd), "cd", len) && len == (int)ft_strlen("cd")) || \
		(!ft_strncmp(str_tolower(cmd), "exit", len) && len == (int)ft_strlen("exit"))))
		return (1);
	return (0);
}

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
		if (ft_strlen(cmd->argv[0]))
		{
			while (path[i])
			{
				bin_path = ft_strdup(path[i]);
				bin_path = clean_strjoin(bin_path, "/");
				bin_path = clean_strjoin(bin_path, cmd->argv[0]);
				found = access(bin_path, X_OK);
				if (!found)
					break ;
				free(bin_path);
				bin_path = NULL;
				i++;
			}
		}
		if (!bin_path)
			printf("minishell: %s: command not found\n", cmd->argv[0]);
	}
	return (bin_path);
}

int		exec_cmd(t_simpleCmd *cmd, int is_builtin, char ***env, char **path)
{
	char	*bin_path;
	int		exit_status;

	bin_path = NULL;
	exit_status = 0;
	if (!redirections(cmd->redirs,(int *)&cmd->fds))
		return (1);
	if (is_builtin)
		exit_status = exec_builtin(cmd, env);
	else
	{
		bin_path = find_binary(cmd, path);
		if (!bin_path)
			exit_status = 127;
		else
		{
		redirect(cmd);
		if (execve(bin_path, cmd->argv, *env) < 0)
			return (minishell_perror(1, bin_path, NULL));
		}
	}
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

int		get_exit_code(int exit_code)
{
	if (WIFSIGNALED(exit_code))
		return(128 + WTERMSIG(exit_code));
	else if (WIFSTOPPED(exit_code))
		return (WSTOPSIG(exit_code));
	else if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	else
		return (exit_code);
}

int		wait_cmds(t_simpleCmd *s_cmd)
{
	int exit_code;

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
	pid_t		pid;

	while (s_cmd)
	{
		pid = fork();
		if (!pid)
			exit(exec_cmd(s_cmd, builtin, env, path));
		close(s_cmd->fds[READ_END]);
		close(s_cmd->fds[WRITE_END]);
		s_cmd->pid = pid;
		s_cmd = s_cmd->nxt;
		if (s_cmd)
			builtin = is_builtin(s_cmd->argv[0]);
	}
}

int		executor(char ***env, t_cmd *cmd)
{
	int			exit_code;
	char		**path;
	int			builtin;
	int			tmpin;
	int			tmpout;

	path = get_path(*env);
	exit_code = 0;
	builtin = is_builtin(cmd->cmds->argv[0]);
	if (cmd->count == 1 && builtin)
	{
		if (!redirections(cmd->cmds->redirs, (int *)&cmd->cmds->fds))
			exit_code = 1;
		else
		{
			tmpin = dup(STDIN_FILENO);
			tmpout = dup(STDIN_FILENO);
			redirect(cmd->cmds);
			exit_code = exec_builtin(cmd->cmds, env);
			dup2(tmpin, STDIN_FILENO);
			dup2(tmpout, STDOUT_FILENO);
			close(tmpin);
			close(tmpout);
		}
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
