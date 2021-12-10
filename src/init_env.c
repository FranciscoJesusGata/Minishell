/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:05:34 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/10 17:39:25 by fgata-va         ###   ########.fr       */
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

void	create_init_env(t_env *env)
{
	char	cwd[PATH_MAX];

	env->all = ft_calloc(sizeof(char *), 3);
	getcwd(cwd, sizeof(cwd));
	printf("cwd set on: %s\n", cwd);
	env->all[0] = ft_strjoin("PATH=", cwd);
	env->all[1] = ft_strdup("SHLVL=1");
	env->all[2] = ft_strdup("_= aquí qué va?");
	env->all[3] = NULL;
}

void	init_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (i)
		save_env(env, envp, i);
	else
		create_init_env(env);
}
