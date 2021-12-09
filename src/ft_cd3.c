/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:53:43 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 17:09:12 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**chop_pwd(char **env, char *cwd)
{
	int		i;
	char	**split;

	i = 0;
	split = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			split = ft_split(env[i], '=');
			free(env[i]);
			env[i] = ft_strdup("PWD=");
			env[i] = clean_strjoin(env[i], cwd);
		}
		i++;
	}
	return (split);
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
