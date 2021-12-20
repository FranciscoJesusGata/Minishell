/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:53:43 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/20 16:44:12 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_oldpwd(char **env)
{
	int		i;
	char	cwd[PATH_MAX];
	char	**tmp;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	tmp = ft_calloc(sizeof(char *), get_size(env) + 1);
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	free(env);
	tmp[i] = ft_strdup("OLDPWD=");
	tmp[i] = clean_strjoin(tmp[i], cwd);
	tmp[i + 1] = NULL;
	return (tmp);
}

char	**chop_pwd(char **env, char *cwd)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			free(env[i]);
			env[i] = ft_strdup("PWD=");
			env[i] = clean_strjoin(env[i], cwd);
			return (ft_split(env[i], '='));
		}
		i++;
	}
	env[i] = ft_strdup("PWD=");
	env[i] = clean_strjoin(env[i], cwd);
	return (ft_split(env[i], '='));
}

char	**chop_home(char **env, char **split_home)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
			split_home = ft_split(env[i], '=');
		i++;
	}
	return (split_home);
}

char	*new_oldpwd(char **env, char *tmp, char *cwd, int i)
{
	char	**split;

	split = ft_split(env[i], '=');
	tmp = ft_strdup(split[0]);
	tmp = clean_strjoin(tmp, "=");
	tmp = clean_strjoin(tmp, cwd);
	ft_freearray(split);
	free(env[i]);
	return (tmp);
}

int	looking_for_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
			return (1);
		i++;
	}
	return (0);
}
