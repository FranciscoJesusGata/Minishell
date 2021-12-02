/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:28:42 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/02 12:35:38 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_eq_num(char *argv)
{
	int i;
	int j;
	char *ret;
	char **split;

	i = ft_strlen(argv) - 1;
	j = ft_strlen(argv) - 1;

	while (argv[i - 1] == '=')
		i--;
	if ((j - i) == 1)
		return (ft_strjoin(argv, "\"\""));
	split = ft_split(argv, '=');
	ret = ft_strjoin(split[0], "=\"");
	while (i != j)
	{
		ret = ft_strjoin(ret, "=");
		j--;
	}
	ret = ft_strjoin(ret, "\"");
	return (ret);
}

char	*include_quotes(t_env *env, char *ret, int i)
{
	char **split;
	int eq;

	eq = 0;
	split = ft_split(env->all[i], '=');
	if (split[1])
	{
		ret = ft_strjoin(split[0], "=");
		ret = ft_strjoin(ret, "\"");
		ret = ft_strjoin(ret, split[1]);
		ret = ft_strjoin(ret, "\"");
	}
	else if((ft_strchr(env->all[i], '=')))
			ret = get_eq_num(env->all[i]);
	else
		ret = ft_strdup(env->all[i]);
	return (ret);
}


char **env_to_temp(t_env *env, char **temp)
{
	int i;

	i = 0;
	temp = ft_calloc(sizeof(char*), get_size(env->all) + 1);
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
			if (ft_strncmp(array[j], array[j + 1], 4) > 0)
			{
				tmp = array[j];
				array[j] = array[j+1];
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
	char **tmp;

	tmp = ft_split(argv, '=');
	if (!ft_strncmp(env, tmp[0], ft_strlen(tmp[0])))
		return (1);
	return (0);
}

char	**create_env(t_env *env, int argc, char **argv)
{
	int i;
	int c;
	char **temp;

	i = 0;
	c = 1;
	temp = ft_calloc(sizeof(char*), (get_size(env->all) + (argc - c) + 2));
	while (env->all[i])
	{
		temp[i] = ft_strdup(env->all[i]);
		i++;
	}
	i = 0;
	while (temp[i])
	{
		if(argv[c] && check_env_exists(temp[i], argv[c]))
		{
			temp[i] = ft_strdup(argv[c]);
			c++;
			if (c < argc)
				i = -1;
		}
		else
			temp[i] = ft_strdup(temp[i]);
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
	//Falla cuando:
	// input: PATH=hola pepe
	// output: no hace PATH

	int	arr_size;
	char **tmp;

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

