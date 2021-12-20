/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:06:21 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/20 13:06:31 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_pwd(char **env, char *split_home)
{
	int		i;
	char	**split_pwd;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		{
			split_pwd = ft_split(env[i], '=');
			free(env[i]);
			break ;
		}
		i++;
	}
	env[i] = ft_strdup("PWD=");
	env[i] = clean_strjoin(env[i], split_home);
	env[i + 1] = NULL;
}
