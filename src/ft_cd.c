/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:17:46 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 16:53:56 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
	return (env);
}

char	**check_path(char **env, char *path)
{
	char	cwd[PATH_MAX];

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