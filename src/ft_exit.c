/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:14:30 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/29 11:56:42 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		ft_exit(int i)
{
	//		Hay que liberar información alocada
	//		La i es un código de error

	exit(i);
	return (0);
}

