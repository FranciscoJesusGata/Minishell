/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:28:42 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/18 14:27:23 by fportalo         ###   ########.fr       */
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
		if (argv[ft_strlen(tmp[0])] != '=')
			return (2);
		ft_freearray(tmp);
		return (1);
	}
	ft_freearray(tmp);
	return (0);
}

char	**copy_envs(char **temp, char **argv, int argc, int c)
{
	int	i;

	while (c < argc)
	{
		i = 0;
		while (temp[i])
		{
			if (argv[c] && check_env_exists(temp[i], argv[c]))
			{
				temp[i] = if_exist_copy(temp[i], argv[c]);
				c++;
				if (c < argc)
					i = -1;
			}
			else
				temp[i] = clean_strdup(temp[i]);
			i++;
		}
		temp[i] = new_env(argc, argv, temp[i], c);
		c++;
	}
	return (temp);
}

char	**create_env(char **env, int argc, char **argv)
{
	int		i;
	int		c;
	char	**temp;

	i = 0;
	c = 1;
	temp = ft_calloc(sizeof(char *), (get_size(env) + (argc - c) + 2));
	while (env[i])
	{
		temp[i] = clean_strdup(env[i]);
		i++;
	}
	free(env);
	i = 0;
	temp = copy_envs(temp, argv, argc, c);
	return (temp);
}

int	ft_export(int argc, char **argv, char ***env)
{
	int		arr_size;
	char	**tmp;
	int		i;

	tmp = NULL;
	if (argc > 1)
		*env = create_env(*env, argc, argv);
	else
	{
		arr_size = get_size(*env);
		tmp = env_to_temp(*env);
		tmp = bubble_sort(tmp, arr_size);
		display_str(tmp, arr_size, 1);
	}
	i = 1;
	while (argv[i])
	{
		if (!valid_export(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
