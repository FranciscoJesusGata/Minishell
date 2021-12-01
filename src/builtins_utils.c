/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:26:30 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/01 15:29:38 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_size(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void display_str(char **splitted, int arr_size, int export_flag)
{
	int i;

	i = 0;
	while(i < arr_size)
	{
		printf("%d %d ", i, arr_size);
		if (export_flag)
			printf("declare -x ");
		printf("%s\n", splitted[i]);
		i++;
	}
}

void ft_freearray(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}
