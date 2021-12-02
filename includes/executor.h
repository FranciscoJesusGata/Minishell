/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:16:22 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/02 16:19:01 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR
# define EXECUTOR
# include "minishell.h"


void	executor(t_env *env, t_cmd *cmd);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	ft_echo(int argc, char **argv);
int		ft_export(int argc, char **argv, t_env *env);
void	ft_unset(int argc, char **argv, t_env *envp);

int		ft_exit(int i);

int		get_size(char **env);
void	display_str(char **splitted, int arr_size, int export_flag);
void	ft_freearray(char **array);
char	*clean_strjoin(char *ret, char *join);

#endif
