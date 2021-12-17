/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:49:41 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/17 17:29:04 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_echo_flag(int argc, char **argv, int i)
{
	int	j;

	j = 0;
	while (i < argc && argv[i][j] == '-')
	{
		j++;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == '\0')
		{
			j = 0;
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (argc == 1)
		write(1, "\n", 1);
	else if (argc > 1)
	{
		i = ft_echo_flag(argc, argv, i);
		if (i >= 2)
			n++;
		while (i < argc)
		{
			ft_putstr_fd(argv[i], 1);
			if ((i + 1) != argc)
				write(1, " ", 1);
			i++;
		}
		if (!n)
			write(1, "\n", 1);
	}
	return (0);
}
