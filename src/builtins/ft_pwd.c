/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:33:57 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/04 11:22:02 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (cwd != NULL)
		printf("PWD=%s\n", cwd);
	else
		perror("bad pwd");
	return (0);
}
