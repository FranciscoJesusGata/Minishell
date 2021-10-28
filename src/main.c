/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/28 15:32:53 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_list *tokens)
{
	while (tokens)
	{
		printf("token [%p]: \"%s\"\n", tokens->content, (char *)tokens->content);
		tokens = tokens->next;
	}
}

int		main()
{
	char	*line;
	t_list	*tokens;

	welcome();
	while (1)
	{
		line = launch_term();
		if (!line)
			break;
		if (*line)
		{
			tokens = lexer(line);
			print_tokens(tokens);
		}
		free(line);
		ft_lstclear(&tokens, free);
	}
	clear_history();
	system("leaks minishell");
}
