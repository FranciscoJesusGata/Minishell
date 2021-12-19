/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:09:21 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 22:24:24 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_lexer *lexer, char *line, char **env)
{
	char	*tmp;
	char	*expanded;

	tmp = divide_str(line, lexer->start, lexer->end);
	expanded = ft_getenv(tmp, env);
	if (expanded)
		concat(&lexer->buffer, expanded);
	else
		concat(&lexer->buffer, ft_strdup(""));
	lexer->start = lexer->end;
	free(tmp);
}

void	expand_exclamation(t_lexer *lexer)
{
	concat(&lexer->buffer, ft_itoa(g_struct.exit_code));
	lexer->end++;
	lexer->start = lexer->end;
}

char	*ft_getenv(char *search, char **env)
{
	int		i;
	char	*expanded;
	int		j;

	i = 0;
	expanded = NULL;
	if (search)
	{
		if (!ft_strncmp(search, "$", 1))
			return (ft_strdup("$"));
		while (env[i])
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			if (!ft_strncmp(env[i], search, j) && j == (int)ft_strlen(search))
				return (ft_substr(env[i], j + 1, ft_strlen(env[i])));
			i++;
		}
	}
	return (expanded);
}
