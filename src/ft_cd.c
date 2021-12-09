/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:17:46 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 16:04:02 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

char	**edit_oldpwd(char **env)
{
	int		i;
	char	cwd[PATH_MAX];
	char	**tmp;
	char	**split;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	tmp = ft_calloc(sizeof(char *), get_size(env) + 1);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))
		{
			split = ft_split(env[i], '=');
			tmp[i] = ft_strdup(split[0]);
			tmp[i] = clean_strjoin(tmp[i], "=");
			tmp[i] = clean_strjoin(tmp[i], cwd);
			ft_freearray(split);
			free(env[i]);
		}
		else
			tmp[i] = clean_strdup(env[i]);
		i++;
	}
	free(env);
	tmp[i] = NULL;
	return (tmp);
}

char	**home_to_pwd(char **env)
{
	int i;
	int j;
	char **split_home;
	char **split_pwd;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
			split_home = ft_split(env[i], '=');
		i++;
	}
	i = 0;
	while(env[i])
	{
		if(!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
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

char	**pwd_to_home(char **env, int j)
{
	int i;
	char **split_home;
	char **split_pwd;

	i = 0;
	while(env[i])			// mirar esto
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
			split_home = ft_split(env[i], '=');
		i++;
	}
	i = 0;
	while(env[i])
	{
		if(!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
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

int	is_home(char **env)
{
	int i;
	char **split;

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

int		ft_chdir(char **env)
{
	int i;
	int dir_nbr;
	char **split;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
			split = ft_split(env[i], '=');
		i++;
	}
	dir_nbr = chdir(split[1]);
	ft_freearray(split);
	return (dir_nbr);
}

char	**change_pwd(char **env, char *cwd)
{
	int i;
	char **split;

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
	return (env);
}

char	**check_path(char **env, char *path)
{
	char cwd[PATH_MAX];

	if (!chdir(path))
	{
		getcwd(cwd, sizeof(cwd));
		change_pwd(env, cwd);
	}
	else
		printf("cd: no such file or directory: %s\n", path);
	return (env);
}

void	ft_cd(int argc, char **argv, t_env *env)
{
	if (argc > 1 && ft_strncmp(argv[1], "~", 1))
		check_path(env->all, argv[1]);
	else
	{
		if (is_home(env->all))
		{
			if (look_for_oldpwd(env->all))
				env->all = create_oldpwd(env->all);
			else
				env->all = edit_oldpwd(env->all);
			env->all = home_to_pwd(env->all);
		}
		ft_chdir(env->all);
	}
}
