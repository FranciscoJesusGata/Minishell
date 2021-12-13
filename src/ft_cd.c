/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:17:46 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/11 21:17:56 by fgata-va         ###   ########.fr       */
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

int	ft_chdir(char **env)
{
	int		i;
	int		dir_nbr;
	char	**split;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
			split = ft_split(env[i], '=');
		i++;
	}
	dir_nbr = chdir(split[1]);
	if (dir_nbr != 0)
		printf("cd: %s: %s\n", strerror(errno), split[1]);
	ft_freearray(split);
	return (dir_nbr);
}

void	change_pwd(char **env, char *cwd)
{
	int		i;
	char	**split;

	i = 0;
	split = NULL;
	split = chop_pwd(env, cwd);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
		{
			free(env[i]);
			env[i] = ft_strdup("OLDPWD=");
			env[i] = clean_strjoin(env[i], split[1]);
		}
		i++;
	}
	ft_freearray(split);
}

char	*join_home(char **env, char *path)
{
	int		i;
	char	**split;
	char	*join;

	i = 0;
	join = NULL;
	split = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
			split = ft_split(env[i], '=');
		i++;
	}
	if (split)
	{
		join = ft_strjoin(split[1], path + 1);
		ft_freearray(split);
	}
	return (join);
}


void	check_path(char **env, char *path)
{
	char	cwd[PATH_MAX];

	if (!ft_strncmp(path, "~", 1))
	{
		path = join_home(env, path);
		if (!path)
			return ;
	}
	if (!chdir(path))
	{
		getcwd(cwd, sizeof(cwd));
		change_pwd(env, cwd);
	}
	else
		printf("cd: %s: %s\n", strerror(errno), path);
}

void	ft_cd(int argc, char **argv, char ***env)
{
	if (argc > 1)
		check_path(*env, argv[1]);
	else
	{
		if (is_home(*env) && ft_chdir(*env) >= 0)
		{
			if (look_for_oldpwd(*env))
				*env = create_oldpwd(*env);
			else
				*env = edit_oldpwd(*env);
			*env = home_to_pwd(*env);
		}
	}
}
