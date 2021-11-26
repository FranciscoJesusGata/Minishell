/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:16:22 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/26 16:44:56 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR
# define EXECUTOR
# include "minishell.h"


void	executor(t_env *env, t_cmd *cmd);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	ft_echo(int argc, char **argv);


#endif
