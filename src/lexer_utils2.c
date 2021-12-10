/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:09:21 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/10 12:09:42 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *env, char *expanded)
{
	char	**split;

	split = ft_split(env, '=');
	expanded = ft_strdup(split[1]);
	ft_freearray(split);
	return (expanded);
}

char	*ft_getenv(char *tmp, t_env *env)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = NULL;
	if (!ft_strncmp(tmp, "$", ft_strlen("$")))
		return (ft_strdup("$"));
	while (env->all[i])
	{
		if (!ft_strncmp(env->all[i], tmp, ft_strlen(tmp)))
		{
			expanded = expand(env->all[i], expanded);
			return (expanded);
		}
		i++;
	}
	return (ft_strdup("\n"));
}
