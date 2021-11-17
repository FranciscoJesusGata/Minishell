/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:49:41 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/16 12:57:58 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>


int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *str, const char *n, size_t len)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if ((int)ft_strlen(n) == 0)
		return ((char *)str);
	while (i < ((int)len) && str[i] != '\0')
	{
		if (n[0] == str[i])
		{
			while (n[j] != '\0' && n[j] == str[i + j] && (i + j) < (int)len)
			{
				if (n[j + 1] == '\0')
					return ((char *)&str[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s != '\0')
		{
			write(fd, s, 1);
			s++;
		}
	}
}

int	ft_echo_flag(char **argv, int i)
{
	int j;

	j = 0;
	while (argv[i][j] == '-')
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

int	main(int argc, char **argv, char **envp)
{
	// Voy a dar por hecho que el executor será el responsable de analizar el token
	// y determinar si es echo, en ese caso, lo enviará aquí
	// El echo tendrá en el segundo argumento (i = 1) un flag o un token para imprimir, pero
	// En este programa, puesto que argv[0] == "a.out", argv[1] == "echo", nuestro programa empezará con i = 2 como
	// primer argumento de nuestro echo

	int i;
	int n;

	i = 2;
	n = 0;
	if (argc == 1)
	{
		write(1, "Prueba a introducir a.out echo (args)\n", ft_strlen("Prueba a introducir a.out echo (args)\n"));
		return (0);
	}
	if (argc == 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	else if(argc > 2)
	{
		i = ft_echo_flag(argv, i);
		if (i > 2)
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

