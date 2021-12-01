/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:20:28 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/01 14:52:50 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
