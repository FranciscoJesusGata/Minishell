/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:28:42 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/29 12:43:26 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void display_str(char **splitted, int arr_size)
{
	int i;

	i = 0;
	while(i < arr_size)
	{
		printf("declare -x ");
		printf("%s\n", splitted[i]);
		i++;
	}
}

char	*include_quotes(t_env *env, char *ret, int i)
{
	char **split;

	split = ft_split(env->all[i], '=');
	ret = ft_strjoin(split[0], "=");
	ret = ft_strjoin(ret, "\"");
	ret = ft_strjoin(ret, split[1]);
	ret = ft_strjoin(ret, "\"");
	return (ret);
}

char **env_to_temp(t_env *env, char **temp)
{
	int i;

	i = 0;
	while (env->all[i])
		i++;
	temp = malloc(sizeof(char*) * i);
	i = 0;
	while (env->all[i])
	{
		temp[i] = include_quotes(env, temp[i], i);
		i++;
	}
	return (temp);
}

char	**bubble_sort(char **array, int array_size)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	while (i < array_size -1)
	{
		j = 0;
		while (j < array_size - i - 1)
		{
			if(ft_strncmp(array[j], array[j + 1], 4) > 0)
			{
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (array);
}

char	**create_env(t_env *env, int argc, char **argv)
{
	int i;
	int c;
	char **temp;

	i = 0;
	c = 1;
	temp = ft_calloc(sizeof(char*), (get_size(env) + (argc - c) + 2));
	while (env->all[i])
	{
		temp[i] = ft_strdup(env->all[i]);
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

int ft_export(int argc, char **argv, t_env *env)
{
	int	arr_size;

	if (argc > 1)
		env->all = create_env(env, argc, argv);
	else
	{
		argv = NULL;
		arr_size = get_size(env);
		env->all = env_to_temp(env, env->all);
		env->all = bubble_sort(env->all, arr_size);
		display_str(env->all, arr_size);
	}
	return (0);
}

