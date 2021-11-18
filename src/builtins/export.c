/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:28:42 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/18 15:21:46 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////
//         LIBFT STUFF         //
/////////////////////////////////

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}


char	*ft_strdup(const char *s1)
{
	char			*s2;
	size_t			l;
	unsigned int	i;

	i = 0;
	l = ft_strlen(s1);
	s2 = (char *)malloc(l + 1);
	if (s2)
	{
		while (s1[i] != '\0' && i < l)
		{
			s2[i] = s1[i];
			i++;
		}
		s2[i] = '\0';
	}
	else
		return (0);
	return (s2);
}

int	ft_wrds(char const *s, char c)
{
	int	wrds;
	int	wrd_fnd;

	wrds = 0;
	wrd_fnd = 0;
	while (*s != '\0')
	{
		if (*s != c && wrd_fnd == 0)
		{
			wrds++;
			wrd_fnd = 1;
		}
		else if (*s == c)
			wrd_fnd = 0;
		s++;
	}
	return (wrds);
}

int	ft_chars(char const *s, char c)
{
	int	cs;

	cs = 0;
	while (*s != c && *s != '\0')
	{
		cs++;
		s++;
	}
	return (cs);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	ft_del_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	*matrix = NULL;
}

void	ft_fillstr(int j, char **wrds, char const *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		wrds[j][i++] = *s;
		s++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc(size * count);
	if (!s)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**wrds;
	int		wrd_l;
	int		j;

	if (!s)
		return (NULL);
	wrds = ft_calloc(ft_wrds(s, c) + 1, sizeof(char *));
	j = 0;
	while (*s && wrds)
	{
		while (*s == c)
			s++;
		wrd_l = ft_chars(s, c);
		if (wrd_l)
		{
			wrds[j] = ft_calloc((wrd_l + 1), sizeof(char));
			if (!wrds[j])
				ft_del_matrix(wrds);
			ft_fillstr(j, wrds, s, c);
			s += wrd_l;
		}
		j++;
	}
	return (wrds);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n == 0)
	{
		return (0);
	}
	i = 0;
	while (((unsigned char)s1[i] != 0 || (unsigned char)s2[i] != 0) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (((unsigned char)s1[i] != (unsigned char)s2[i]) && i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}


/////////////////////////////////
//      DISPLAY STR EXPORT     //
/////////////////////////////////


void display_str(char **splitted, int arr_size)
{
	int i;

	i = 0;
	while(i < arr_size)
	{
		printf("%s\n", splitted[i]);
		i++;
	}
}

char **str_to_temp(char **splitted, char **temp)
{
	int i;

	i = 0;
	while (splitted[i])
		i++;
	temp = malloc(sizeof(char*) * i);
	i = 0;
	while (splitted[i])
	{
		temp[i] = ft_strdup(splitted[i]);
		i++;
	}
	return (temp);
}

char	**bubble_sort(char **arr, int arr_size)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	while (i < arr_size -1)
	{
		j = 0;
		while (j < arr_size - i - 1)
		{
			if(ft_strncmp(arr[j], arr[j + 1], 4) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

int	get_size(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
		i++;
	return (i);
}

int main(int argc, char **argv, char **envp)
{
	int	arr_size;
	char **temp;

	argv = NULL;
	arr_size = get_size(envp);
	temp = str_to_temp(envp, temp);
	temp = bubble_sort(temp, arr_size);
	display_str(temp, arr_size);
	return (0);
}
