/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:58:10 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/18 13:07:24 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**kill_env(char **env, int dead)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char *), get_size(env) + 1);
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

int	equal_id(char *argv, char *env)
{
	int	len;
	int	diff;

	if (!argv || !env)
		return (0);
	len = ft_strlen(argv);
	diff = ft_strncmp(env, argv, len);
	if (!diff && env[len] == '=')
		return (1);
	return (0);
}


int	valid_unset(char *arg)
{
	int	i;

	if (arg[0] < 'A' || arg[0] > 'z')
		return (0);
	i = 1;
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > 'z' || (arg[i] > '9' && arg[i] < 'A')))
			return (0);
		i++;
	}
	return (1);
}

char	**if_some_argc(char **tmp, int argc, char **argv)
{
	int	i;
	int	nb;

	nb = 1;
	if (argc > 1)
	{
		while (nb < argc)
		{
			i = 0;
			if (valid_unset(argv[nb]))
			{
				while (tmp[i])
				{
					if (equal_id(argv[nb], tmp[i]))
						tmp = kill_env(tmp, i);
					i++;
				}
			}
			else
				printf("minishell: unset: '%s': not a valid identifier\n", \
						argv[nb]);
			nb++;
		}
	}
	return (tmp);
}

int	ft_unset(int argc, char **argv, char ***env)
{
	int		i;
	int		arg_nb;
	char	**tmp;

	i = 0;
	arg_nb = 1;
	tmp = ft_calloc(sizeof(char *), get_size(*env) + 1);
	while ((*env)[i])
	{
		tmp[i] = ft_strdup((*env)[i]);
		i++;
	}
	tmp = if_some_argc(tmp, argc, argv);
	ft_freearray(*env);
	*env = tmp;
	i = 1;
	while(argv[i])
	{
		if (!valid_unset(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
