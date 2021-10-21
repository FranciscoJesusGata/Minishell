/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:14:00 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/21 12:33:57 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_list **tokens, char *format, int start, int len)
{
	char	*sub_str;

	sub_str = ft_substr(format, start, len);
	if (sub_str)
		ft_lstadd_back(tokens, ft_lstnew(sub_str));
}

t_list	*lexer(char *line)
{
	int	start;
	int	len;
	t_list	*tokens;

	start = 0;
	len = 0;
	tokens = NULL;
	while (line[len])
	{
		if (line[len] == 32)
		{
			create_token(&tokens, line, start, len);
			len++;
			start = len;
			continue ;
		}
		len++;
	}
	create_token(&tokens, line, start, len);
	return (tokens);
}

