/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:24:04 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/11 18:26:10 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_eq_num(char *argv)
{
	int		i;
	int		j;
	char	*ret;
	char	**split;

	i = ft_strlen(argv) - 1;
	j = ft_strlen(argv) - 1;
	while (argv[i - 1] == '=')
		i--;
	if ((j - i) == 1)
		return (ft_strjoin(argv, "\"\""));
	split = ft_split(argv, '=');
	ret = ft_strjoin(split[0], "=\"");
	ft_freearray(split);
	while (i != j)
	{
		ret = ft_strjoin(ret, "=");
		j--;
	}
	ret = ft_strjoin(ret, "\"");
	return (ret);
}

char	*include_quotes(char **env, char *ret, int i)
{
	char	**split;
	int		eq;

	eq = 0;
	split = ft_split(env[i], '=');
	if (split[1])
	{
		ret = clean_strjoin(split[0], "=");
		ret = clean_strjoin(ret, "\"");
		ret = ft_strjoin(ret, split[1]);
		ret = clean_strjoin(ret, "\"");
	}
	else if ((ft_strchr(env[i], '=')))
		ret = get_eq_num(env[i]);
	else
		ret = ft_strdup(env[i]);
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
		temp[i] = include_quotes(env, temp[i], i);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
