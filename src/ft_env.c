/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:20:28 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/17 15:50:51 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **env)
{
	int		i;
	int		size;
	char	**split;

	i = 0;
	size = get_size(env);
	while (i < size)
	{
		split = ft_split(env[i], '=');
		if (env[i][ft_strlen(split[0])] == '=')
			printf("%s\n", env[i]);
		ft_freearray(split);
		i++;
	}
}
