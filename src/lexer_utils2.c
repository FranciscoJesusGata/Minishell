/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:09:21 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/11 18:05:53 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *env)
{
	char	**split;
	char	*expanded;

	split = ft_split(env, '=');
	expanded = ft_strdup(split[1]);
	ft_freearray(split);
	return (expanded);
}

char	*ft_getenv(char *tmp, char **env)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = NULL;
	if (!ft_strncmp(tmp, "$", ft_strlen("$")))
		return (ft_strdup("$"));
	while (env[i])
	{
		if (!ft_strncmp(env[i], tmp, ft_strlen(tmp)))
		{
			expanded = expand(env[i]);
			return (expanded);
		}
		i++;
	}
	return (ft_strdup("\n"));
}
