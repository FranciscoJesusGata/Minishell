/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:09:06 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/20 13:07:16 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int		ft_env(char **env, char **argv, int argc);
int		ft_echo(int argc, char **argv);
int		ft_export(int argc, char **argv, char ***env);
int		ft_unset(int argc, char **argv, char ***envp);
int		ft_exit(char **argv, int argc);
int		ft_cd(int argc, char **argv, char ***env);
int		ft_pwd(void);
int		get_size(char **env);
void	display_str(char **splitted, int arr_size, int export_flag);
void	ft_freearray(char **array);
char	*clean_strjoin(char *ret, char *join);
char	*clean_strdup(char *s);
char	*if_exist_copy(char *temp, char *argv);
int		check_env_exists(char *env, char *argv);
char	*get_eq_num(char *argv);
char	*include_quotes(char *env);
char	**env_to_temp(char **env);
int		is_home(char **env);
char	**pwd_to_home(char **env, int j);
char	**home_to_pwd(char **env);
char	**edit_oldpwd(char **env);
int		look_for_oldpwd(char **env);
char	**chop_pwd(char **env, char *cwd);
char	**chop_home(char **env, char **split_home);
void	search_pwd(char **env, char *split_home);
char	**create_oldpwd(char **env);
char	*new_oldpwd(char **env, char *tmp, char *cwd, int i);
int		valid_unset(char *arg);
int		valid_export(char *arg);
char	*new_env(int argc, char **argv, char *temp, int c);
int		looking_for_home(char **env);

#endif
