/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:26:30 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/11 20:27:31 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	display_str(char **splitted, int arr_size, int export_flag)
{
	int	i;

	i = 0;
	while (i < arr_size)
	{
		if (export_flag)
			printf("declare -x ");
		printf("%s\n", splitted[i]);
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	ft_freearray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

char	*clean_strjoin(char *s1, char *s2)
{
	char	*tmp;
	char	*ret;

	tmp = s1;
	ret = ft_strjoin(s1, s2);
	free(tmp);
	return (ret);
}

char	*clean_strdup(char *s)
{
	char	*tmp;
	char	*ret;

	tmp = s;
	ret = ft_strdup(s);
	free(tmp);
	return (ret);
}
