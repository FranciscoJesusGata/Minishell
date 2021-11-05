/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:25 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/05 12:18:59 by fportalo         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*tokens;
	t_env	env;

	argc = 0;
	argv = NULL;
	init_env(&env, envp);
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
		ft_lstclear(&tokens, free);
	}
	clear_history();
	system("leaks minishell");
}
