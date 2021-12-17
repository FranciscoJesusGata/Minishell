/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:16:22 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/17 17:01:11 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR
# define EXECUTOR
# include "minishell.h"

int		executor(char ***env, t_cmd *cmd);

/*
** File redirection and pipes management functions
*/
int		redirections(t_redir *redirections, int *fds);
void	redirect(t_simpleCmd *cmd);
#endif
