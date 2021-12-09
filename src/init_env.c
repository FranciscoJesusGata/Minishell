/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:05:34 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 15:46:25 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_env(t_env *env, char **envp, int i)
{
	env->all = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (envp[i])
	{
		env->all[i] = ft_strdup(envp[i]);
		i++;
	}
}

char	**chop_paths(char *raw_path)
{
	char **paths;

	raw_path += 5;
	paths = ft_split(raw_path, ':');
	return (paths);
}

void	get_def_env(t_env *env, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (ft_strnstr(env->all[j], "PWD", 3))
			env->pwd = ft_strdup(env->all[j]) + 4;
		if (ft_strnstr(env->all[j], "HOME", 4))
			env->home = ft_strdup(env->all[j]) + 5;
		if (ft_strnstr(env->all[j], "USER", 4))
			env->user = ft_strdup(env->all[j]) + 5;
		else if (ft_strnstr(env->all[j], "PATH", 4))
			env->path = chop_paths(env->all[j]);
		j++;
	}
}

void	create_init_env(t_env *env)
{
	char	cwd[PATH_MAX];

	env->all = ft_calloc(sizeof(char *), 3);
	getcwd(cwd, sizeof(cwd));
	printf("cwd set on: %s\n", cwd);
	env->all[0] = ft_strjoin("PATH=", cwd);
	env->all[1] = ft_strdup("SHLVL=1");
	env->all[2] = ft_strdup("_= Aquí va el último comando usado o su dirección");
	env->all[3] = NULL;
}

void	init_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (i)
	{
		save_env(env, envp, i);
		get_def_env(env, i);
	}
	else
		create_init_env(env);
}
