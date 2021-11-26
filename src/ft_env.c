/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:20:28 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/26 16:29:38 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_size(char **envs)
{
	int i;

	i = 0;
	while (envs[i])
		i++;
	return (i);
}

void ft_env (t_env *env)
{
	int i;

	i = 0;

	while(i < get_size(env->all))
	{
		printf("%s\n", env->all[i]);
		i++;
	}
}

