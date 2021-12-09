/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:44:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 17:08:36 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_home(char **env)
{
	int		i;
	char	**split;

	i = 0;
	split = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
		{
			split = ft_split(env[i], '=');
			if (!split[1])
				env = pwd_to_home(env, i);
			ft_freearray(split);
			return (1);
		}
		i++;
	}
	printf("minishell: cd: HOME not set\n");
	return (0);
}

char	**pwd_to_home(char **env, int j)
{
	int		i;
	char	**split_home;
	char	**split_pwd;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
			split_home = ft_split(env[i], '=');
		i++;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
			split_pwd = ft_split(env[i], '=');
		i++;
	}
	free(env[j]);
	env[j] = ft_strdup("HOME=");
	env[j] = clean_strjoin(env[j], split_pwd[1]);
	ft_freearray(split_home);
	ft_freearray(split_pwd);
	return (env);
}

char	**home_to_pwd(char **env)
{
	int		i;
	int		j;
	char	**split_home;
	char	**split_pwd;

	i = 0;
	split_home = NULL;
	split_home = chop_home(env, split_home);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			split_pwd = ft_split(env[i], '=');
			j = i;
		}
		i++;
	}
	free(env[j]);
	env[j] = ft_strdup("PWD=");
	env[j] = clean_strjoin(env[j], split_home[1]);
	ft_freearray(split_home);
	ft_freearray(split_pwd);
	return (env);
}

char	**edit_oldpwd(char **env)
{
	int		i;
	char	cwd[PATH_MAX];
	char	**tmp;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	tmp = ft_calloc(sizeof(char *), get_size(env) + 1);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
			tmp[i] = new_oldpwd(env, tmp[i], cwd, i);
		else
			tmp[i] = clean_strdup(env[i]);
		i++;
	}
	free(env);
	tmp[i] = NULL;
	return (tmp);
}

int	look_for_oldpwd(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
			return (0);
		i++;
	}
	return (1);
}
