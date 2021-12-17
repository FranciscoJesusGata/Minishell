/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:16:22 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/17 16:39:27 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

int		executor(char ***env, t_cmd *cmd);
void	ft_pwd(void);

/*
** File redirection and pipes management functions
*/
int		redirections(t_redir *redirections, int *fds);
void	redirect(t_simpleCmd *cmd);
void	create_pipes(t_simpleCmd *cmds);

#endif
