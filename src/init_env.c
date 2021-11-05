/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:05:34 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/05 13:32:04 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_env(t_env *env, char **envp, int i)
{
	env->all = malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i])
	{
		env->all[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	get_def_env(t_env *env, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (ft_strnstr(env->all[j], "PWD", 3))
			env->pwd = ft_strdup(env->all[j]);
		else if (ft_strnstr(env->all[j], "PATH", 4))
			env->path = ft_strdup(env->all[j]);
		j++;
	}
}

void	create_env(t_env *env)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	env->pwd = ft_strjoin("PATH=", cwd);
	env->shlvl = ft_strdup("SHLVL=1");
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
		create_env(env);
}
