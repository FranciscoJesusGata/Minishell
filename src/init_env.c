/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:05:34 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 17:08:18 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sum_shlvl(char *env)
{
	int		shl_count;
	char	*shl_char;
	char	**split;
	char	*tmp;

	split = ft_split(env, '=');
	shl_count = ft_atoi(split[1]) + 1;
	tmp = ft_strjoin(split[0], "=");
	shl_char = ft_itoa(shl_count);
	tmp = clean_strjoin(tmp, shl_char);
	free(shl_char);
	ft_freearray(split);
	return (tmp);
}

char	**save_env(char **envp, int i)
{
	char	**env;

	env = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
			env[i] = sum_shlvl(envp[i]);
		else
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
