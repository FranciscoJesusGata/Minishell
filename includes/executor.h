/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:16:22 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 22:51:54 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

int		executor(char ***env, t_cmd *cmd);
int		exec_builtin(t_simpleCmd *cmd, char ***env);
int		exec_cmd(t_simpleCmd *cmd, int is_builtin, char ***env, char **path);

/*
** Executor utils functions
*/
int		is_builtin(char *cmd);
char	*find_binary(char *arg, char **path);
int		get_exit_code(int exit_code);
char	**get_path(char **envp);

/*
** File redirection and pipes management functions
*/
int		redirections(t_redir *redirections, int *fds, char **env);
void	link_fds(int *fds, int file, int io);
void	redirect(t_simpleCmd *cmd);
void	create_pipes(t_simpleCmd *cmds);
int		heredoc(char *delimiter, int quoted, char **env);
int		open_files(t_redir *redirections, int *in, int *out, char **env);

#endif
