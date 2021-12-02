/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:28:42 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/02 18:03:16 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**bubble_sort(char **array, int array_size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (i < array_size - 1)
	{
		j = 0;
		while (j < array_size - i - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], 4) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (array);
}

int	check_env_exists(char *env, char *argv)
{
	char	**tmp;

	tmp = ft_split(argv, '=');
	if (!ft_strncmp(env, tmp[0], ft_strlen(tmp[0])))
	{
		ft_freearray(tmp);
		return (1);
	}
	ft_freearray(tmp);
	return (0);
}

char	**copy_envs(char **temp, char **argv, int argc, int c)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (argv[c] && check_env_exists(temp[i], argv[c]))
		{
			free(temp[i]);
			temp[i] = ft_strdup(argv[c]);
			c++;
			if (c < argc)
				i = -1;
		}
		else
			temp[i] = clean_strdup(temp[i]);
		i++;
	}
	while (c < argc)
	{
		temp[i] = ft_strdup(argv[c]);
		i++;
		c++;
	}
	return (temp);
}

char	**create_env(t_env *env, int argc, char **argv)
{
	int		i;
	int		c;
	char	**temp;

	i = 0;
	c = 1;
	temp = ft_calloc(sizeof(char *), (get_size(env->all) + (argc - c) + 2));
	while (env->all[i])
	{
		temp[i] = clean_strdup(env->all[i]);
		i++;
	}
	free(env->all);
	i = 0;
	temp = copy_envs(temp, argv, argc, c);
	return (temp);
}

int	ft_export(int argc, char **argv, t_env *env)
{
	int		arr_size;
	char	**tmp;

	tmp = NULL;
	if (argc > 1)
		env->all = create_env(env, argc, argv);
	else
	{
		arr_size = get_size(env->all);
		tmp = env_to_temp(env, env->all);
		tmp = bubble_sort(tmp, arr_size);
		display_str(tmp, arr_size, 1);
	}
	return (0);
}
