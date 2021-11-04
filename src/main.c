/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/04 16:23:07 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_list	*tokens;

	welcome();
	while (1)
	{
		line = launch_term();
		if (!line)
			break ;
		if (*line)
		{
			tokens = lexer(line);
			print_tokens(tokens);
		}
		free(line);
		ft_lstclear(&tokens, delete_token);
	}
	clear_history();
	system("leaks minishell");
}
