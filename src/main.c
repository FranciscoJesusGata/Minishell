/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/17 16:35:09 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_list	*tokens;
	t_cmd	*cmd;

	welcome();
	line = launch_term();
	while (line)
	{
		if (*line)
		{
			tokens = lexer(line);
			print_tokens(tokens);
			cmd = parser(tokens);
			print_cmd(cmd);
			delete_cmd(&cmd);
			ft_lstclear(&tokens, delete_token);
		}
		free(line);
		line = launch_term();
	}
	clear_history();
	system("leaks minishell");
}
