/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:24:04 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 17:26:11 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*include_quotes(char *env)
{
	char	*ret;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(env, '=');
	ret = ft_strdup(split[0]);
	if (env[ft_strlen(split[0])] == '=')
	{
		ret = clean_strjoin(ret, "=\"");
		env += ft_strlen(ret) - 1;
		ret = clean_strjoin(ret, env);
		ret = clean_strjoin(ret, "\"");
	}
	ft_freearray(split);
	return (ret);
}

char	**env_to_temp(char **env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_calloc(sizeof(char *), get_size(env) + 1);
	while (env[i])
	{
		temp[i] = include_quotes(env[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

char	*if_exist_copy(char *temp, char *argv)
{
	if (check_env_exists(temp, argv) == 1)
	{
		free(temp);
		temp = ft_strdup(argv);
	}
	return (temp);
}

char	*new_env(int argc, char **argv, char *temp, int c)
{
	if (c != argc)
	{
		if (valid_export(argv[c]))
			temp = ft_strdup(argv[c]);
		else
			printf("minishell: export: %s: not a valid identifier\n", argv[c]);
	}
	return (temp);
}
