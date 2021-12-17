/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:14:58 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/16 15:19:26 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_export(char *arg)
{
	int	i;

	if (arg[0] < 'A' || arg[0] > 'z')
		return (0);
	i = 1;
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > 'z' || (arg[i] > '9' && arg[i] < 'A')))
		{
			if (arg[i] != '=' && (i != (int)ft_strlen(arg)))
				return (0);
		}
		i++;
	}
	return (1);
}
