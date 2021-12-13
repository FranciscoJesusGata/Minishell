/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:09:21 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/13 17:18:56 by fgata-va         ###   ########.fr       */
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

char	*ft_getenv(char *search, char **env)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = NULL;
	if (search)
	{
		if (!ft_strncmp(search, "$", ft_strlen("$")))
			return (ft_strdup("$"));
		while (env[i])
		{
			if (!ft_strncmp(env[i], search, ft_strlen(search)))
			{
				expanded = expand(env[i]);
				return (expanded);
			}
			i++;
		}
	}
	return (expanded);
}
