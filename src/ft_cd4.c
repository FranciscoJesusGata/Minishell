/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:06:21 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/20 16:48:33 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**search_pwd(char **env, char *split_home)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			free(env[i]);
			tmp = ft_strdup("PWD=");
			env[i] = clean_strjoin(tmp, split_home);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}
