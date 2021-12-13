/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:09:06 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/11 18:53:19 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

void	ft_env(char **env);
void	ft_echo(int argc, char **argv);
int		ft_export(int argc, char **argv, char ***env);
void	ft_unset(int argc, char **argv, char ***envp);
void	ft_exit(char *arg);
void	ft_cd(int argc, char **argv, char ***env);
int		get_size(char **env);
void	display_str(char **splitted, int arr_size, int export_flag);
void	ft_freearray(char **array);
char	*clean_strjoin(char *ret, char *join);
char	*clean_strdup(char *s);
char	*get_eq_num(char *argv);
char	*include_quotes(char **env, char *ret, int i);
char	**env_to_temp(char **env);
int		is_home(char **env);
char	**pwd_to_home(char **env, int j);
char	**home_to_pwd(char **env);
char	**edit_oldpwd(char **env);
int		look_for_oldpwd(char **env);
char	**chop_pwd(char **env, char *cwd);
char	**chop_home(char **env, char **split_home);
char	*new_oldpwd(char **env, char *tmp, char *cwd, int i);

#endif
