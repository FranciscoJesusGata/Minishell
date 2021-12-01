/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:58:10 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/01 17:43:38 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**kill_env(char **env, int dead)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char *), get_size(env));
	while (env[i])
	{
		if (i != dead)
		{
			tmp[j] = ft_strdup(env[i]);
			j++;
		}
		free(env[i]);
		i++;
	}
	free(env);
	return (tmp);
}

int		equal_id(char *argv, char *env)
{
	int len;
	int diff;

	if (!argv || !env)
		return (0);
	len = ft_strlen(argv);
	diff = ft_strncmp(env, argv, len);
	if (!diff && env[len] == '=')
		return (1);
	return (0);
}

void	ft_unset(int argc, char **argv, t_env *env)
{
	int i;
	int arg_nb;
	char **tmp;

	i = 0;
	arg_nb = 1;
	tmp = ft_calloc(sizeof(char *), get_size(env->all) + 1);
	while (env->all[i])
	{
		tmp[i] = ft_strdup(env->all[i]);
		i++;
	}

	if (argc > 1)
	{
		while (arg_nb < argc)
		{
			i = 0;
			while (tmp[i])
			{
				if (equal_id(argv[arg_nb], tmp[i]))
				{
					tmp = kill_env(tmp, i);
				}
				i++;
			}
			arg_nb++;
		}
	}
	i = 0;
	ft_freearray(env->all);
	env->all = tmp;
	display_str(env->all, get_size(env->all), 0);
	system("leaks minishell");
}
