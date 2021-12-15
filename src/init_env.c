/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:05:34 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/13 19:08:52 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**save_env(char **envp, int i)
{
	char	**env;
	env = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

char	**create_init_env(void)
{
	char	cwd[PATH_MAX];
	char	**env;

	env = ft_calloc(sizeof(char *), 3);
	getcwd(cwd, sizeof(cwd));
	env[0] = ft_strjoin("PATH=", cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

char	**init_env(char **envp)
{
	int		i;

	g_exit_code = 0;
	i = 0;
	while (envp[i])
		i++;
	if (i)
		return (save_env(envp, i));
	return (create_init_env());
}
