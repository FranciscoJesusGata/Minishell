/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:20:28 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/18 15:35:07 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_env(char **env, char **argv, int argc)
{
	int		i;
	int		size;
	char	**split;

	i = 0;
	if (argc > 1)
	{
		printf("env: %s: No such file or directory\n", argv[1]);
		return (127);
	}
	size = get_size(env);
	while (i < size)
	{
		split = ft_split(env[i], '=');
		if (env[i][ft_strlen(split[0])] == '=')
			printf("%s\n", env[i]);
		ft_freearray(split);
		i++;
	}
	return (0);
}
