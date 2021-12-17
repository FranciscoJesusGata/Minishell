/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:14:30 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/17 17:05:14 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


int	all_digit(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_atoi(arg))
			arg++;
		else
			return (0);
	}
	return (1);
}

int	ft_exit(char **argv, int argc)
{
	if (argv[1])
	{
		if (all_digit(argv[1]))
		{
			if (argc < 3)
				exit(ft_atoi(argv[1]));
			else
			{
				printf("minishell: exit: too many argumenteiros\n");
				return (1);
			}
		}
		else
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", argv[1]);
			exit(255);
		}
	}
	printf("exit\n");
	exit(0); // <-- cambiar por el g_exit_code <--
	return (0);
}
